/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:08:28 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/24 14:34:45 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	usleep(1000);
	while (true)
	{
		if (philo_died(philo, table))
		{
			write_status(DEAD, philo, table);
			safe_sem_handle(&table->write_semaphore, NULL, SEM_LOCK, table);
			safe_sem_handle(&table->death_semaphore, NULL, SEM_UNLOCK, table);
			return (NULL);
		}
		if (get_bool(philo->philo_semaphore, table, &philo->full))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	philo_routine(t_philo philo)
{
	t_table	*table;
	sem_t	sem;

	table = philo.table;
	philo.philo_semaphore = &sem;
	safe_sem_handle(&philo.philo_semaphore, NULL, SEM_INIT, table);
	safe_sem_handle(&philo.table->start_semaphore, NULL, SEM_LOCK, table);
	safe_sem_handle(&philo.table->start_semaphore, NULL, SEM_UNLOCK, table);
	set_long(philo.philo_semaphore, table, &philo.last_meal_time,
		get_time(MILLISECOND));
	if (!safe_thread_handle(&philo.monitor, monitor_routine, &philo, CREATE))
		exit(EXIT_FAILURE);
	safe_thread_handle(&philo.monitor, NULL, NULL, DETACH);
	de_sync_philos(&philo, philo.table);
	while (true)
	{
		if (philo.full)
			break ;
		philo_eat(&philo, table);
		write_status(SLEEPING, &philo, table);
		usleep(philo.table->time_to_sleep);
		philo_think(&philo, table);
		usleep(1000);
	}
	sem_destroy(philo.philo_semaphore);
	exit(EXIT_SUCCESS);
}

void	*death_monitor_thread(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	safe_sem_handle(&table->death_semaphore, NULL, SEM_LOCK, table);
	i = 0;
	while (++i < table->philo_number)
	{
		if (table->philos[i].process_id > 0)
			kill(table->philos[i].process_id, SIGKILL);
	}
	return (NULL);
}

bool	dinner_init(t_table *table)
{
	int	i;

	if (table->nbr_limit_meals == 0 || table->philo_number == 0)
		return (true);
	safe_thread_handle(&table->death_thread, death_monitor_thread, table,
		CREATE);
	safe_thread_handle(&table->death_thread, NULL, NULL, DETACH);
	//i = -1;
	//while (++i < table->philo_number)
	//{
	//	safe_sem_handle(&table->start_semaphore, NULL, SEM_UNLOCK, table);
	//	safe_sem_handle(&table->start_semaphore, NULL, SEM_UNLOCK, table);
	//}
	safe_sem_handle(&table->start_semaphore, NULL, SEM_UNLOCK, table);
	i = -1;
	while (++i < table->philo_number)
		waitpid(table->philos[i].process_id, NULL, 0);
	return (true);
}
