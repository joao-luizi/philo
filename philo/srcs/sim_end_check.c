/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_end_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:02:10 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/25 13:19:56 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*finish_sim(t_philo *philos)
{
	pthread_mutex_lock(philos->info->monitor);
	philos->info->finish_sim = 1;
	pthread_mutex_unlock(philos->info->monitor);
	usleep(10);
	log_state(DEAD, philos);
	return (NULL);
}

void	eat_check(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->info->number_of_philo)
	{
		pthread_mutex_lock(philos->info->monitor);
		if (philos[i].times_eaten < philos->info->times_must_eat)
		{
			pthread_mutex_unlock(philos->info->monitor);
			return ;
		}
		pthread_mutex_unlock(philos->info->monitor);
	}
	pthread_mutex_lock(philos->info->monitor);
	philos->info->finish_sim = 1;
	pthread_mutex_unlock(philos->info->monitor);
	log_state(SATISFIED, philos);
}

void	*death_check(void *philo)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)philo;
	pthread_mutex_lock(philos->info->monitor);
	pthread_mutex_unlock(philos->info->monitor);
	while (!philos->info->finish_sim)
	{
		usleep(1000);
		i = -1;
		while (++i < philos->info->number_of_philo)
		{
			pthread_mutex_lock(philos->info->monitor);
			if (gettimems() - philos[i].last_meal
				>= (suseconds_t)philos[i].info->time_to_die)
			{
				pthread_mutex_unlock(philos->info->monitor);
				return (finish_sim(&philos[i]));
			}
			pthread_mutex_unlock(philos->info->monitor);
		}
		if (philos->info->times_must_eat != -1)
			eat_check(philos);
	}
	return (NULL);
}
