/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:58:56 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/26 13:42:29 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

static bool	philo_full(t_philo *philo)
{
	int				local_limit_meals;
	unsigned int	local_meal_counter;

	if (!safe_get(&local_limit_meals, &philo->shared->nbr_limit_meals,
			philo->philo_semaphore, TYPE_INT))
		return (ft_putstr_fd("Failed to safely get nbr_limit_meals\n", 2),
			true);
	if (!safe_get(&local_meal_counter, &philo->meal_counter,
			philo->philo_semaphore, TYPE_UINT))
		return (ft_putstr_fd("Failed to safely get meal_counter\n", 2), true);
	if (local_limit_meals > 0 && (int)local_meal_counter == local_limit_meals)
	{
		if (!safe_set(&philo->full, &(bool){true}, philo->philo_semaphore,
			TYPE_BOOL))
			return (ft_putstr_fd("Failed to safely set philo full\n", 2), true);
		return (true);
	}
	return (false);
}

bool	philo_died(t_philo *philo)
{
	unsigned int	elapsed;

	if (sem_wait(philo->philo_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock philo semaphore\n", 2), true);
	if (philo->full || philo->last_meal_time == 0)
	{
		if (sem_post(philo->philo_semaphore) != 0)
			return (ft_putstr_fd("Failed to unlock philo semaphore\n", 2),
				false);
		return (false);
	}
	elapsed = get_time(MILLISECOND) - philo->last_meal_time;
	if (elapsed > philo->shared->time_to_die / 1000)
	{
		if (sem_post(philo->philo_semaphore) != 0)
			return (ft_putstr_fd("Failed to unlock philo semaphore\n", 2),
				true);
		return (true);
	}
	if (sem_post(philo->philo_semaphore) != 0)
		return (ft_putstr_fd("Failed to unlock philo semaphore\n", 2), false);
	return (false);
}

void	philo_think(t_philo *philo)
{
	unsigned int	local_philo_number;
	unsigned int	local_time_to_think;

	write_states(THINKING, philo);
	if (!safe_get(&local_philo_number, &philo->shared->philo_number,
			philo->philo_semaphore, TYPE_UINT))
	{
		ft_putstr_fd("Failed to safely get philo_number2\n", 2);
		return ;
	}
	if (!safe_get(&local_time_to_think, &philo->shared->time_to_think,
			philo->philo_semaphore, TYPE_UINT))
	{
		ft_putstr_fd("Failed to safely get time_to_think\n", 2);
		return ;
	}
	if (local_philo_number % 2 == 0)
		usleep(local_time_to_think * 0.1);
	else
		usleep(local_time_to_think * 0.5);
}

static bool	take_forks(t_philo *philo)
{
	if (sem_wait(philo->shared->forks_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock forks semaphore\n", 2), false);
	if (!write_states(TAKE_FIRST_FORK, philo))
		return (false);
	if (sem_wait(philo->shared->forks_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock forks semaphore\n", 2), false);
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
	if (!safe_set(&philo->last_meal_time, &current_time, philo->philo_semaphore,
			TYPE_SIZE_T))
		return (ft_putstr_fd("Failed to set last_meal_time\n", 2), false);
	if (!safe_increase(&philo->meal_counter, philo->philo_semaphore, TYPE_UINT))
		return (ft_putstr_fd("Failed to increase meal_counter\n", 2), false);
	usleep(shared->time_to_eat);
	if (philo_full(philo))
	{
		if (!safe_set(&philo->full, &(bool){true}, philo->philo_semaphore,
			TYPE_BOOL))
			return (ft_putstr_fd("Failed to set philo full\n", 2), false);
	}
	if (sem_post(philo->shared->forks_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock forks semaphore\n", 2), false);
	if (sem_post(philo->shared->forks_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock forks semaphore\n", 2), false);
	return (true);
}
