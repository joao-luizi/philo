/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:25 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/26 12:18:17 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

static void	clean_philos(t_table **table)
{
	t_philo	*philos;
	int		i;

	if (!(*table)->philos)
		return ;
	philos = (*table)->philos;
	i = 0;
	while (i < (int)(*table)->shared->philo_number)
	{
		if (philos[i].monitor_thread)
			free(philos[i].monitor_thread);
		if (philos[i].philo_semaphore)
		{
			sem_destroy(philos[i].philo_semaphore);
			free(philos[i].philo_semaphore);
		}
		i++;
	}
	free((*table)->philos);
}

static void clean_shared_aux(t_shared *shared)
{
	if (shared->write_semaphore)
	{
		sem_close(shared->write_semaphore);
		sem_unlink("/write_semaphore");
	}
	if (shared->forks_semaphore)
	{
		sem_close(shared->forks_semaphore);
		sem_unlink("/forks_semaphore");
	}
	if (shared->death_semaphore)
	{
		sem_close(shared->death_semaphore);
		sem_unlink("/death_semaphore");
	}
}
static void	clean_shared(t_shared *shared)
{
	if (!shared)
		return ;
	if (shared->start_semaphore)
	{
		sem_close(shared->start_semaphore);
		sem_unlink("/start_semaphore");
	}
	if (shared->table_semaphore)
	{
		sem_close(shared->table_semaphore);
		sem_unlink("/table_semaphore");
	}
	clean_shared_aux(shared);
	free(shared);
}
/**
 * @brief Cleans up resources used by the table.
 *
 * This function destroys all mutexes associated with
 * philosophers and forks,
 * then frees the memory allocated for the philosophers
 * and forks.
 *
 * @param table The table to clean up.
 */
void	clean_table(t_table **table)
{
	if (!table || !*table)
		return ;
	clean_philos(table);
	clean_shared((*table)->shared);
	if ((*table)->parent_monitor_thread)
		free((*table)->parent_monitor_thread);
	free(*table);
	*table = NULL;
}
