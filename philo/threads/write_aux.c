/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:04:36 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 00:04:37 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	write_dead(t_philo *philo, long elapsed)
{
	printf(W "%-6ld" RST " %d is dead\n", elapsed, philo->id);
}

void	write_thinking(t_philo *philo, long elapsed)
{
	printf(W "%-6ld" RST " %d is thinking\n", elapsed, philo->id);
}

void	write_sleeping(t_philo *philo, long elapsed)
{
	printf(W "%-6ld" RST " %d is sleeping\n", elapsed, philo->id);
}

void	write_eating(t_philo *philo, long elapsed)
{
	printf(W "%-6ld" RST " %d is eating\n", elapsed, philo->id);
}

void	write_take_fork(t_philo *philo, long elapsed)
{
	printf(W "%-6ld" RST " %d has taken a fork\n", elapsed, philo->id);
}
