# include "../inc/philo.h"

void *lone_philo(void * data)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)data;
    table = philo->table;
    wait_all_threads(table);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    increase_long(&table->table_mutex, &table->thread_running_count);
    write_status(TAKE_FIRST_FORK, philo, table);
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
    while (!get_bool(&table->table_mutex, &table->end_simulation))
    {
        i = 0;
        while (i < table->philo_number && !get_bool(&table->table_mutex, &table->end_simulation))
        {
            if (philo_died(table->philos + i, table))
            {
                write_status(DEAD, table->philos + i, table);
                set_bool(&table->table_mutex, &table->end_simulation, true);
            }
            i++;
        }
    }
    return (NULL);
}
void de_sync_philos(t_philo *philo, t_table *table)
{
    if (table->philo_number % 2 == 0)
    {
        if (philo->id % 2 == 0)
            custom_usleep(30000, table);
    }
    else
    {
        if (philo->id % 2 == 0)
            philo_think(philo, table);
    }
}
void *dinner_simulation(void *data)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)data;
    table = philo->table;

    wait_all_threads(table);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    increase_long(&table->table_mutex, &table->thread_running_count);
    de_sync_philos(philo, table);
    while (!get_bool(&table->table_mutex, &table->end_simulation))
    {
        if (philo->full)
            break ;
        philo_eat(philo, table);
        write_status(SLEEPING, philo, table);
        custom_usleep(table->time_to_sleep, table);
        philo_think(philo, table);
    }
    return (NULL);
}
bool join_all_threads(t_table *table)
{
    int i;

    i = -1;
    while (++i < table->philo_number)
    {
        if (!safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN))
            return (false);
    }
    set_bool(&table->table_mutex, &table->end_simulation, true);
    if (!safe_thread_handle(&table->monitor, NULL, NULL, JOIN))
        return (false);
    return (true);
}
bool dinner_init(t_table *table)
{
    int i;

    if (table->nbr_limit_meals == 0 || table->philo_number == 0)
        return (true);
    {
        i = -1;
        while (++i < table->philo_number)
        {
            if (table->philo_number < 2)
            {
                if (!safe_thread_handle(&table->philos[0].thread_id, lone_philo,  &table->philos[0], CREATE))
                    return (false);
            }
            else
            {
                if (!safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE))
                return (false);
            }
        }
    }
    if (!safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE))
        return (false);
    table->start_simulation = get_time(MILLISECOND);
    set_bool(&table->table_mutex, &table->all_threads_ready, true);
    if (!join_all_threads(table))
        return (false);
    return (true);
}

bool table_init(t_table *table)
{
	int i;

	table->end_simulation = false;
	table->all_threads_ready = false;
    table->thread_running_count = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_number);
    if (!table->philos)
        return (false);
    if (!safe_mutex_handle(&table->table_mutex, INIT))
        return (false);
    if (!safe_mutex_handle(&table->write_mutex, INIT))
        return (false);
    table->forks = safe_malloc(sizeof(t_fork) * table->philo_number);
    if (!table->forks)
        return (false);
    i = 0;
	while (i < table->philo_number)
	{
		if (!safe_mutex_handle(&table->forks[i].fork, INIT))
            return (false);
		table->forks[i].fork_id = i;
		i++;
	}
	return (true);
}
