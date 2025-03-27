/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:31 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/27 11:43:56 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/message.h"
#include "inc/philo.h"

bool	write_states(t_status status, t_philo *philo)
{
	unsigned int	elapsed;

	if (sem_wait(philo->shared->write_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock write semaphore\n", 2), false);
	elapsed = (get_time(MICROSECOND) - philo->shared->start_simulation) / 1000;
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
	if (sem_post(philo->shared->write_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock write semaphore\n", 2), false);
	return (true);
}

static bool	de_sync_philos(t_philo *philo)
{
	unsigned int	local_philo_number;
	unsigned int	local_philo_id;

	if (sem_wait(philo->philo_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock philo semaphore\n", 2), false);
	local_philo_number = philo->shared->philo_number;
	local_philo_id = philo->id;
	if (sem_post(philo->philo_semaphore) != 0)
		return (ft_putstr_fd("Failed to unlock philo semaphore\n", 2), false);
	if (local_philo_number % 2 == 0)
	{
		if (local_philo_id % 2 == 0)
			usleep(40000);
	}
	else
	{
		if (local_philo_id % 2 == 0)
			philo_think(philo);
	}
	return (true);
}

static bool	philo_setup(t_philo *philo)
{
	if (sem_wait(philo->philo_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock table semaphore\n", 2), false);
	if (pthread_create(philo->monitor_thread, NULL, philosopher_monitor,
			philo) != 0)
		return (ft_putstr_fd("Failed to create process monitor thread\n", 2),
			false);
	pthread_detach(*philo->monitor_thread);
	if (sem_wait(philo->shared->start_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock start_semaphore\n", 2), false);
	philo->last_meal_time = get_time(MICROSECOND);
	if (sem_post(philo->shared->start_semaphore) != 0)
		return (ft_putstr_fd("Failed to unlock table semaphore\n", 2), false);
	if (sem_post(philo->philo_semaphore) != 0)
		return (ft_putstr_fd("Failed to unlock table semaphore\n", 2), false);
	return (true);
}

void	philo_life(t_philo *philo)
{
	bool	philo_full;

	if (!philo_setup(philo))
		exit(1);
	if (!de_sync_philos(philo))
		exit(1);
	while (true)
	{
		philo_eat(philo, philo->shared);
		if (!safe_get(&philo_full, &philo->full, philo->philo_semaphore,
				TYPE_BOOL))
			return (ft_putstr_fd("Failed to get philo_full\n", 2), (void)0);
		write_states(SLEEPING, philo);
		custom_sleep(philo->shared->time_to_sleep);
		philo_think(philo);
		if (philo_full)
			break ;
		usleep(100);
	}
	exit(0);
}
