/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:04:43 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/21 23:08:05 by joao             ###   ########.fr       */
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
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING)
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING)
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING)
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DEAD)
		printf("%-6ld %d is dead\n", elapsed, philo->id);
	safe_sem_handle(&table->write_semaphore, NULL, SEM_UNLOCK, table);
}
