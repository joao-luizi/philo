/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:37:49 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/25 13:02:06 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	grab_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		log_state(FORK, philo);
		pthread_mutex_lock(philo->r_fork);
		log_state(FORK, philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		log_state(FORK, philo);
		pthread_mutex_lock(philo->l_fork);
		log_state(FORK, philo);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	eating_sleeping(t_philo *philo)
{
	grab_forks(philo);
	log_state(EATING, philo);
	pthread_mutex_lock(philo->info->monitor);
	philo->last_meal = gettimems();
	pthread_mutex_unlock(philo->info->monitor);
	in_action(philo, philo->info->time_to_eat);
	drop_forks(philo);
	pthread_mutex_lock(philo->info->monitor);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->info->monitor);
	log_state(SLEEPING, philo);
	in_action(philo, philo->info->time_to_sleep);
	log_state(THINKING, philo);
}

void	*single_philo(t_philo *philo)
{
	log_state(FORK, philo);
	in_action(philo, philo->info->time_to_die);
	return (NULL);
}

void	*philo_func(void *philo)
{
	t_philo	*philos;

	philos = (t_philo *)philo;
	pthread_mutex_lock(philos->info->monitor);
	philos->last_meal = gettimems();
	pthread_mutex_unlock(philos->info->monitor);
	if (philos->info->number_of_philo == 1)
		return (single_philo(philos));
	if (philos->id % 2 == 0)
		usleep(philos->info->number_of_philo);
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(philos->info->monitor);
		if (philos->info->finish_sim)
		{
			pthread_mutex_unlock(philos->info->monitor);
			return (philos);
		}
		pthread_mutex_unlock(philos->info->monitor);
		eating_sleeping(philos);
	}
	return (NULL);
}
