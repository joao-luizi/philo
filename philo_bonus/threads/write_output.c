/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:04:43 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/21 16:02:57 by joaomigu         ###   ########.fr       */
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
	safe_sem_handle(&table->write_semaphore, NULL, SEM_LOCK, table);
	elapsed = get_time(MILLISECOND) - table->start_simulation;
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
		write_take_fork(philo, elapsed);
	else if (status == EATING)
		write_eating(philo, elapsed);
	else if (status == SLEEPING)
		write_sleeping(philo, elapsed);
	else if (status == THINKING)
		write_thinking(philo, elapsed);
	else if (status == DEAD)
		write_dead(philo, elapsed);
	safe_sem_handle(&table->write_semaphore, NULL, SEM_UNLOCK, table);
}
