/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:25 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/27 12:01:11 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

/**
 * @brief Frees and destroys the shared data structure used by all 
 * philosophers.
 *

	* This function safely destroys and frees the shared mutexes 
	(`table_mutex` and `write_mutex`)
 * and finally frees the `shared` structure itself.
 *
 * @param shared Pointer to the shared data structure.
 */
static void	clean_shared(t_shared *shared)
{
	if (shared)
	{
		pthread_mutex_destroy(&shared->table_mutex);
		pthread_mutex_destroy(&shared->write_mutex);
		free(shared);
	}
}

/**
 * @brief Frees and destroys all fork mutexes in the table.
 *
 * Iterates through each fork in the `table` and destroys the corresponding
 * mutex. Afterwards, it frees the entire fork array.
 *
 * @param table Double pointer to the table structure containing the forks.
 */
static void	clean_forks(t_table **table)
{
	unsigned int	i;

	if (!(*table)->forks)
		return ;
	i = 0;
	while (i < (*table)->shared->philo_number)
	{
		pthread_mutex_destroy(&(*table)->forks[i].fork);
		i++;
	}
	free((*table)->forks);
}

/**
 * @brief Frees and destroys all philosopher data in the table.
 *
 * This function iterates through all philosopher structures in the table,
 * destroying their individual mutexes and freeing their allocated memory.
 * It also frees the monitor thread (if allocated) and the philosopher array.
 *

	* @param table Double pointer to the table structure containing the 
	philosophers.
 */
static void	clean_philos(t_table **table)
{
	unsigned int	i;

	if (!(*table)->philos)
		return ;
	i = 0;
	while (i < (*table)->shared->philo_number)
	{
		pthread_mutex_destroy(&(*table)->philos[i].philo_mutex);
		i++;
	}
	free((*table)->philos);
}

/**
 * @brief Fully cleans up and deallocates the table structure.
 *
 * This function acts as a complete cleanup routine. It calls sub-cleanup
 * functions to destroy forks, philosophers, and shared data. It then frees

	* the table structure itself and sets the pointer to NULL to avoid 
	dangling references.
 *

	* @param table Double pointer to the table structure to be cleaned 
	and deallocated.
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
