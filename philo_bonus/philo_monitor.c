/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:17 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/27 11:09:08 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/message.h"
#include "inc/philo.h"

void	*death_monitor_thread(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	sem_wait(table->shared->death_semaphore);
	i = 0;
	while (i < (int)table->shared->philo_number)
	{
		if (table->philos[i].process_id > 0)
			kill(table->philos[i].process_id, SIGKILL);
		i++;
	}
	return (NULL);
}

void	*philosopher_monitor(void *arg)
{
	t_philo			*philo;
	size_t			current_time;
	unsigned int	local_ttodie;
	size_t			local_last_meal;

	philo = (t_philo *)arg;
	if (sem_wait(philo->philo_semaphore) != 0)
		return (ft_putstr_fd("Failed to lock table semaphore\n", 2), NULL);
	local_ttodie = philo->shared->time_to_die;
	sem_post(philo->philo_semaphore);
	while (1)
	{
		current_time = get_time(MICROSECOND);
		safe_get(&local_last_meal, &philo->last_meal_time,
			philo->philo_semaphore, TYPE_SIZE_T);
		if (current_time - local_last_meal > local_ttodie)
		{
			write_states(DEAD, philo);
			sem_wait(philo->shared->write_semaphore);
			sem_post(philo->shared->death_semaphore);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
