# include "../inc/philo.h"

void *lone_philo(void * data)
{
    t_philo *philo;
    t_table *table;

    table = get_table(NULL);
    philo = (t_philo *)data;
    wait_all_threads(table);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    increase_long(&table->table_mutex, &table->thread_running_count);
    write_status(TAKE_FIRST_FORK, philo);
    while (!get_bool(&table->table_mutex, &table->end_simulation))
        usleep(30);
    return (NULL);
}
void *monitor_dinner(void *data)
{
    t_table *table;
    int i;

    table = (t_table *)data;
    while (!all_threads_running(&table->table_mutex, &table->thread_running_count, table->philo_number))
        ;
    //printf("Monitor: All threads running!\n");
    while (!get_bool(&table->table_mutex, &table->end_simulation))
    {
        i = 0;
        while (i < table->philo_number && !get_bool(&table->table_mutex, &table->end_simulation))
        {
            if (philo_died(table->philos + i, table))
            {
                write_status(DEAD, table->philos + i);
                set_bool(&table->table_mutex, &table->end_simulation, true);
            }
            i++;
        }
    }
    return (NULL);
}
void de_sync_philos(t_philo *philo)
{
    t_table *table;

    table = get_table(NULL);

    if (table->philo_number % 2 == 0)
    {
        if (philo->id % 2 == 0)
            custom_usleep(30000, table);
    }
    else
    {
        if (philo->id % 2 == 0)
            philo_think(philo);
    }
}
void *dinner_simulation(void *data)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)data;
    table = get_table(NULL);
    wait_all_threads(table);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    increase_long(&table->table_mutex, &table->thread_running_count);
    de_sync_philos(philo);
    while (!get_bool(&table->table_mutex, &table->end_simulation))
    {
        if (philo->full)
            break ;
        philo_eat(philo);
        write_status(SLEEPING, philo);
        //printf("Im going to sleep for %ld\n", table->time_to_sleep);
        custom_usleep(table->time_to_sleep, table);
        philo_think(philo);
    }

    return (NULL);
}

void dinner_init(t_table *table)
{
    int i;

    if (table->nbr_limit_meals == 0 || table->philo_number == 0)
        return ;
    if (table->philo_number < 2)
        safe_thread_handle(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE);
    else
    {
        i = 0;
        while (i < table->philo_number)
        {
            safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
            i++;
        }
    }
    safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
    table->start_simulation = get_time(MILLISECOND);
    set_bool(&table->table_mutex, &table->all_threads_ready, true);
    i = 0;
    while (i < table->philo_number)
    {
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
        i++;
    }
    set_bool(&table->table_mutex, &table->end_simulation, true);
    safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}

void table_init(t_table *table)
{
	int i;

	table->end_simulation = false;
	table->all_threads_ready = false;
    table->thread_running_count = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_number);
	safe_mutex_handle(&table->table_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_number);
	i = 0;
	while (i < table->philo_number)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
}