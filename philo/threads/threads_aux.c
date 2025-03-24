/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:04:25 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/24 14:54:04 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Waits for all threads to be ready.
 *
 * This function waits until all threads are ready by checking the
 * all_threads_ready flag in the table structure.
 *
 * @param table The table structure.
 */
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
	{
		usleep(1000);	
	}
}

/**
 * @brief Checks if all threads are running.
 *
 * This function checks if the number of running threads is equal to the total
 * number of philosophers.
 *
 * @param mutex The mutex protecting the threads counter.
 * @param threads The number of running threads.
 * @param philo_nbr The total number of philosophers.
 * @return True if all threads are running, false otherwise.
 */
bool	all_threads_running(t_mtx *mutex, unsigned int *threads, unsigned int philo_nbr)
{
	bool	result;

	result = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		result = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (result);
}
