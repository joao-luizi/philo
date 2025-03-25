/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:31 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/25 12:34:35 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/message.h"
#include "inc/philo.h"

bool	write_states(t_status status, t_philo *philo)
{
	unsigned int	elapsed;
	bool			local_end_simulation;

	if (pthread_mutex_lock(philo->shared->write_mutex) != 0)
		return (ft_putstr_fd("Failed to lock write mutex\n", 2), false);
	if (!safe_get(&local_end_simulation, &philo->shared->end_simulation,
			philo->shared->table_mutex, TYPE_BOOL))
		return (ft_putstr_fd("Failed to get end_simulation\n", 2), false);
	if (local_end_simulation)
		return (pthread_mutex_unlock(philo->shared->write_mutex), true);
	elapsed = get_time(MILLISECOND) - philo->shared->start_simulation;
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
		printf("%-6u %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING)
		printf("%-6u %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING)
		printf("%-6u %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING)
		printf("%-6u %d is thinking\n", elapsed, philo->id);
	else if (status == DEAD)
		printf("%-6u %d is dead\n", elapsed, philo->id);
	if (pthread_mutex_unlock(philo->shared->write_mutex) != 0)
		return (ft_putstr_fd("Failed to unlock write mutex\n", 2), false);
	return (true);
}

static void	de_sync_philos(t_philo *philo)
{
	t_shared		*shared;
	unsigned int	local_philo_number;
	unsigned int	local_philo_id;

	shared = philo->shared;
	if (!safe_get(&local_philo_number, &shared->philo_number,
			shared->table_mutex, TYPE_UINT))
		return (ft_putstr_fd("Failed to safely get philo_number\n", 2),
			(void)0);
	if (!safe_get(&local_philo_id, &philo->id, philo->philo_mutex, TYPE_UINT))
		return (ft_putstr_fd("Failed to safely get philo_number\n", 2),
			(void)0);
	if (local_philo_number % 2 == 0)
	{
		if (local_philo_id % 2 == 0)
			usleep(30000);
	}
	else
	{
		if (local_philo_id % 2 == 0)
			philo_think(philo);
	}
}

void	*philo_life_single(void *args)
{
	t_philo	*philo;
	bool	local_end_simulation;
	size_t	current_time;

	philo = (t_philo *)args;
	if (!safe_get(&local_end_simulation, &philo->shared->end_simulation,
			philo->shared->table_mutex, TYPE_BOOL))
		return (ft_putstr_fd("Failed to safely get end_simulation\n", 2), NULL);
	current_time = get_time(MILLISECOND);
	if (!safe_set(&philo->last_meal_time, &current_time, philo->philo_mutex,
			TYPE_SIZE_T))
		return (ft_putstr_fd("Failed to safely set last_meal_time\n", 2), NULL);
	if (!write_states(TAKE_FIRST_FORK, philo))
		return (NULL);
	while (!local_end_simulation)
	{
		if (!safe_get(&local_end_simulation, &philo->shared->end_simulation,
				philo->shared->table_mutex, TYPE_BOOL))
			return (ft_putstr_fd("Failed to safely get end_simulation\n", 2),
				NULL);
		usleep(30);
	}
	return (NULL);
}

static bool	philo_setup(t_philo *philo, bool *local_end_simulation)
{
	size_t	current_time;

	if (!safe_get(local_end_simulation, &philo->shared->end_simulation,
			philo->shared->table_mutex, TYPE_BOOL))
		return (ft_putstr_fd("Failed to safely get end_simulation\n", 2),
			false);
	current_time = get_time(MILLISECOND);
	if (!safe_set(&philo->last_meal_time, &current_time, philo->philo_mutex,
			TYPE_SIZE_T))
		return (ft_putstr_fd("Failed to safely set last_meal_time\n", 2),
			false);
	return (true);
}

void	*philo_life_many(void *args)
{
	t_philo	*philo;
	bool	local_end_simulation;
	bool	philo_full;

	philo = (t_philo *)args;
	if (!philo_setup(philo, &local_end_simulation))
		return (NULL);
	de_sync_philos(philo);
	while (!local_end_simulation)
	{
		if (!safe_get(&local_end_simulation, &philo->shared->end_simulation,
				philo->shared->table_mutex, TYPE_BOOL))
			return (ft_putstr_fd("Failed to get end_simulation\n", 2), NULL);
		philo_eat(philo, philo->shared);
		if (!safe_get(&philo_full, &philo->full, philo->philo_mutex, TYPE_BOOL))
			return (ft_putstr_fd("Failed to get philo_full\n", 2), NULL);
		if (philo_full)
			return (NULL);
		write_states(SLEEPING, philo);
		custom_sleep(philo->shared->time_to_sleep / 1000, philo->shared);
		philo_think(philo);
	}
	return (NULL);
}
