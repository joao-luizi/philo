/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:25 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/25 12:36:16 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

static void	clean_shared(t_shared *shared)
{
	if (shared)
	{
		if (shared->table_mutex)
		{
			pthread_mutex_destroy(shared->table_mutex);
			free(shared->table_mutex);
		}
		if (shared->write_mutex)
		{
			pthread_mutex_destroy(shared->write_mutex);
			free(shared->write_mutex);
		}
		free(shared);
	}
}

static void	clean_forks(t_table **table)
{
	unsigned int	i;

	if (!(*table)->forks)
		return ;
	i = 0;
	while (i < (*table)->shared->philo_number)
	{
		if ((*table)->forks[i].fork)
		{
			pthread_mutex_destroy((*table)->forks[i].fork);
			free((*table)->forks[i].fork);
		}
		i++;
	}
	free((*table)->forks);
}

static void	clean_philos(t_table **table)
{
	unsigned int	i;

	if (!(*table)->philos)
		return ;
	i = 0;
	while (i < (*table)->shared->philo_number)
	{
		if ((*table)->philos[i].philo_mutex)
		{
			pthread_mutex_destroy((*table)->philos[i].philo_mutex);
			free((*table)->philos[i].philo_mutex);
			free((*table)->philos[i].thread_id);
		}
		i++;
	}
	if ((*table)->monitor)
		free((*table)->monitor);
	free((*table)->philos);
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
	clean_forks(table);
	clean_philos(table);
	clean_shared((*table)->shared);
	free(*table);
	*table = NULL;
}
