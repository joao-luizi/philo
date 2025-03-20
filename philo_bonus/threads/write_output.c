/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:04:43 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 15:49:31 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Writes the status of a philosopher to the console.
 *
 * This function checks the status of the philosopher and writes
 * the corresponding
 * message to the console. It handles different statuses such as taking forks,
 * eating, sleeping, thinking, and death.
 *
 * @param status The status of the philosopher.
 * @param philo The philosopher structure.
 * @param table The table structure.
 */
void	write_status(t_status status, t_philo *philo, t_table *table)
{
	long	elapsed;

	if (philo->full)
		return ;
	elapsed = get_time(MILLISECOND) - table->start_simulation;
	safe_sem_handle(&table->write_semaphore, NULL, SEM_LOCK, table);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !get_bool(&table->write_semaphore, table, &table->end_simulation))
		write_take_fork(philo, elapsed);
	else if (status == EATING && !get_bool(&table->write_semaphore, table,
			&table->end_simulation))
		write_eating(philo, elapsed);
	else if (status == SLEEPING && !get_bool(&table->write_semaphore, table,
			&table->end_simulation))
		write_sleeping(philo, elapsed);
	else if (status == THINKING && !get_bool(&table->write_semaphore, table,
			&table->end_simulation))
		write_thinking(philo, elapsed);
	else if (status == DEAD && !get_bool(&table->write_semaphore, table,
			&table->end_simulation))
		write_dead(philo, elapsed);
	safe_sem_handle(&table->write_semaphore, NULL, SEM_UNLOCK, table);
}
