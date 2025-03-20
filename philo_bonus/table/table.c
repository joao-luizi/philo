# include "../inc/philo.h"


void *monitor_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
	t_table *table = philo->table;
   
    safe_sem_handle(&philo->table->start_semaphore, NULL, SEM_LOCK, philo->table);
	usleep(1000);
    while (!get_bool(&table->table_semaphore, table, &table->end_simulation))
	{
		if (philo_died(philo, table))
		{
			write_status(DEAD, philo, table);
			set_bool(&philo->philo_semaphore, table, &philo->dead, true);
			set_bool(&table->table_semaphore, table, &table->end_simulation, true);
			break;
		}
		if (get_bool(&philo->philo_semaphore, table, &philo->full))
            break;
	}
	return (NULL);
}

void philo_routine(t_philo philo)
{
	t_table *table;

	table = philo.table;
	safe_sem_handle(&philo.philo_semaphore, NULL, SEM_INIT, table);
	if (!safe_thread_handle(&philo.monitor, monitor_routine, &philo, CREATE))
		exit(EXIT_FAILURE);
	safe_sem_handle(&philo.table->start_semaphore, NULL, SEM_LOCK, table);
	set_long(&philo.philo_semaphore, table, &philo.last_meal_time, get_time(MILLISECOND));
	de_sync_philos(&philo, philo.table);
	while (!get_bool(&table->table_semaphore, table, &table->end_simulation))
	{
		if (philo.full)
			break ;
		philo_eat(&philo,  table);
		write_status(SLEEPING, &philo, table);
		custom_usleep(philo.table->time_to_sleep, table);
		philo_think(&philo, table);
	}
	safe_thread_handle(&philo.monitor, NULL, NULL, JOIN);
	if (philo.dead)
		exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}
