/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:04:36 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/21 23:04:02 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Writes a message to the console indicating that a 
 * philosopher is dead.
 *
 * @param philo The philosopher structure.
 * @param elapsed The time elapsed since the start of the simulation.
 */
void	write_dead(t_philo *philo, long elapsed)
{
	printf("%-6ld %d is dead\n", elapsed, philo->id);
}

/**
 * @brief Writes a message to the console indicating that a 
 * philosopher is thinking.
 *
 * @param philo The philosopher structure.
 * @param elapsed The time elapsed since the start of the simulation.
 */
void	write_thinking(t_philo *philo, long elapsed)
{
	printf("%-6ld %d is thinking\n", elapsed, philo->id);
}

/**
 * @brief Writes a message to the console indicating that a 
 * philosopher is sleeping.
 *
 * @param philo The philosopher structure.
 * @param elapsed The time elapsed since the start of the simulation.
 */
void	write_sleeping(t_philo *philo, long elapsed)
{
	printf("%-6ld %d is sleeping\n", elapsed, philo->id);
}

/**
 * @brief Writes a message to the console indicating that a 
 * philosopher is eating.
 *
 * @param philo The philosopher structure.
 * @param elapsed The time elapsed since the start of the simulation.
 */
void	write_eating(t_philo *philo, long elapsed)
{
	printf("%-6ld %d is eating\n", elapsed, philo->id);
}

/**
 * @brief Writes a message to the console indicating that a 
 * philosopher has taken a fork.
 *
 * @param philo The philosopher structure.
 * @param elapsed The time elapsed since the start of the simulation.
 */
void	write_take_fork(t_philo *philo, long elapsed)
{
	printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
}
