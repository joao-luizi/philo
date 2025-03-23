/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:06:40 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/23 19:08:18 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief De-synchronizes philosophers to prevent simultaneous
 * actions.
 *
 * This function introduces a delay or thinking period for philosophers
 *  to
 * prevent them from taking actions at the same time.
 *
 * @param philo A pointer to the t_philo structure containing the
 * philosopher's data.
 * @param table A pointer to the t_table structure containing the
 * simulation data.
 */
void	de_sync_philos(t_philo *philo, t_table *table)
{
	if (table->philo_number % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(30000);
	}
	else
	{
		if (philo->id % 2 == 0)
			philo_think(philo, table);
	}
}

/**
 * @brief Initializes the table data structure for the process-based 
 * solution.
 *
 * This function initializes the table data structure by creating 
 * semaphores for
 * synchronization and setting up the simulation state. It creates
 *  semaphores for
 * forks, table synchronization, and writing. The forks semaphore 
 * is initialized
 * with a value of 1 and incremented until it matches the total
 *  number of philosophers.
 *
 * The `safe_sem_handle` function is used for all semaphore 
 * operations, ensuring
 * proper error handling. If any semaphore operation fails, 
 * the program exits with
 * an error message, leaving no invalid state.
 *
 * @param table A pointer to the t_table structure containing the 
 * simulation data.
 * @return true if the table was initialized successfully, false 
 otherwise.
 */
bool	table_init(t_table *table)
{
	int	i;

	safe_sem_handle(&table->table_semaphore, "/table_semaphore", UNLINK, table);
	safe_sem_handle(&table->write_semaphore, "/write_semaphore", UNLINK, table);
	safe_sem_handle(&table->start_semaphore, "/start_semaphore", UNLINK, table);
	safe_sem_handle(&table->death_semaphore, "/death_semaphore", UNLINK, table);
	safe_sem_handle(&table->forks, "/forks", UNLINK, table);
	table->end_simulation = false;
	table->process_running_count = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_number);
	safe_sem_handle(&table->forks, "/forks", SEM_CREATE, table);
	i = 0;
	while (++i < table->philo_number)
		safe_sem_handle(&table->forks, "/forks", SEM_UNLOCK, table);
	safe_sem_handle(&table->table_semaphore, "/table_semaphore", SEM_CREATE,
		table);
	safe_sem_handle(&table->write_semaphore, "/write_semaphore", SEM_CREATE,
		table);
	safe_sem_handle(&table->start_semaphore, "/start_semaphore", SEM_CREATE,
		table);
	safe_sem_handle(&table->death_semaphore, "/death_semaphore", SEM_CREATE,
		table);
	safe_sem_handle(&table->death_semaphore, NULL, SEM_LOCK, table);
	safe_sem_handle(&table->start_semaphore, NULL, SEM_LOCK, table);
	return (true);
}
