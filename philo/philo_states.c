/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:58:56 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/26 13:18:08 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

static bool	philo_full(t_philo *philo)
{
	int				local_limit_meals;
	unsigned int	local_meal_counter;
	bool			value;

	if (!safe_get(&local_limit_meals, &philo->shared->nbr_limit_meals,
			philo->shared->table_mutex, TYPE_INT))
		return (ft_putstr_fd("Failed to safely get nbr_limit_meals\n", 2),
			true);
	if (!safe_get(&local_meal_counter, &philo->meal_counter, philo->philo_mutex,
			TYPE_UINT))
		return (ft_putstr_fd("Failed to safely get meal_counter\n", 2), true);
	if (local_limit_meals > 0 && (int)local_meal_counter == local_limit_meals)
	{
		value = true;
		if (!safe_set(&philo->full, &value, philo->philo_mutex, TYPE_BOOL))
			return (ft_putstr_fd("Failed to safely set philo full\n", 2), true);
		return (true);
	}
	return (false);
}

bool	philo_died(t_philo *philo)
{
	unsigned int	elapsed;

	if (pthread_mutex_lock(philo->philo_mutex) != 0)
		return (ft_putstr_fd("Failed to lock philo mutex\n", 2), false);
	if (philo->full || philo->last_meal_time == 0)
	{
		if (pthread_mutex_unlock(philo->philo_mutex) != 0)
			return (ft_putstr_fd("Failed to unlock philo mutex\n", 2), false);
		return (false);
	}
	elapsed = get_time(MILLISECOND) - philo->last_meal_time;
	if (elapsed > philo->shared->time_to_die / 1000)
	{
		if (pthread_mutex_unlock(philo->philo_mutex) != 0)
			return (ft_putstr_fd("Failed to unlock philo mutex\n", 2), true);
		return (true);
	}
	if (pthread_mutex_unlock(philo->philo_mutex) != 0)
		return (ft_putstr_fd("Failed to unlock philo mutex\n", 2), false);
	return (false);
}

void	philo_think(t_philo *philo)
{
	unsigned int	local_philo_number;
	unsigned int	local_time_to_think;

	write_states(THINKING, philo);
	if (!safe_get(&local_philo_number, &philo->shared->philo_number,
			philo->shared->table_mutex, TYPE_UINT))
	{
		ft_putstr_fd("Failed to safely get philo_number\n", 2);
		return ;
	}
	if (!safe_get(&local_time_to_think, &philo->shared->time_to_think,
			philo->shared->table_mutex, TYPE_UINT))
	{
		ft_putstr_fd("Failed to safely get time_to_think\n", 2);
		return ;
	}
	if (local_philo_number % 2 == 0)
		custom_sleep((local_time_to_think / 1000) * 0.1, philo->shared);
	else
		custom_sleep((local_time_to_think / 1000) * 0.5, philo->shared);
}

static bool	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->first_fork->fork) != 0)
		return (ft_putstr_fd("Failed to lock fork mutex\n", 2), false);
	if (!write_states(TAKE_FIRST_FORK, philo))
		return (false);
	if (pthread_mutex_lock(philo->second_fork->fork) != 0)
		return (ft_putstr_fd("Failed to lock fork mutex\n", 2), false);
	if (!write_states(TAKE_SECOND_FORK, philo))
		return (false);
	return (true);
}

bool	philo_eat(t_philo *philo, t_shared *shared)
{
	size_t	current_time;

	take_forks(philo);
	current_time = get_time(MILLISECOND);
	if (!write_states(EATING, philo))
		return (false);
	if (!safe_set(&philo->last_meal_time, &current_time, philo->philo_mutex,
			TYPE_SIZE_T))
		return (ft_putstr_fd("Failed to set last_meal_time\n", 2), false);
	if (!safe_increase(&philo->meal_counter, philo->philo_mutex, TYPE_UINT))
		return (ft_putstr_fd("Failed to increase meal_counter\n", 2), false);
	custom_sleep(shared->time_to_eat / 1000, shared);
	if (philo_full(philo))
	{
		if (!safe_set(&philo->full, &(bool){true}, philo->philo_mutex,
			TYPE_BOOL))
			return (ft_putstr_fd("Failed to set philo full\n", 2), false);
	}
	if (pthread_mutex_unlock(philo->first_fork->fork) != 0)
		return (ft_putstr_fd("Failed to unlock fork mutex\n", 2), false);
	if (pthread_mutex_unlock(philo->second_fork->fork) != 0)
		return (ft_putstr_fd("Failed to unlock fork mutex\n", 2), false);
	return (true);
}
