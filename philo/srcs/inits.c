/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 19:15:26 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/25 13:21:02 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	info_init(t_info *info, int argc, char **argv)
{
	info->number_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->times_must_eat = ft_atoi(argv[5]);
	else
		info->times_must_eat = -1;
	info->philo_satisfied = 0;
	info->finish_sim = 0;
	info->monitor = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(info->monitor, NULL);
}

void	philo_info_init(t_info *info, t_philo *philo,
			pthread_mutex_t *fork_mutex, int philo_id)
{
	philo->id = philo_id;
	if (info->number_of_philo == 1)
		philo->l_fork = NULL;
	else if (philo_id == 1)
		philo->l_fork = &fork_mutex[info->number_of_philo - 1];
	else
		philo->l_fork = &fork_mutex[philo_id - 2];
	philo->r_fork = &fork_mutex[philo_id - 1];
	philo->times_eaten = 0;
	philo->info = info;
}

pthread_mutex_t	*fork_init(t_info *info)
{
	pthread_mutex_t	*fork_mutex;
	int				i;

	fork_mutex = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
	if (!fork_mutex)
		return (NULL);
	i = -1;
	while (++i < info->number_of_philo)
		pthread_mutex_init(&fork_mutex[i], NULL);
	return (fork_mutex);
}

t_philo	*philos_init(t_info *info, pthread_mutex_t *fork_mutex)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * info->number_of_philo);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < info->number_of_philo)
		philo_info_init(info, &philos[i], fork_mutex, i + 1);
	return (philos);
}

void	*threads_init(t_philo *philos)
{
	int				i;

	i = -1;
	pthread_mutex_lock(philos->info->monitor);
	philos->info->start_time = gettimems();
	while (++i < philos->info->number_of_philo)
		pthread_create(&philos[i].tid, NULL, &philo_func, &philos[i]);
	pthread_create(&philos->info->verify_death, NULL, &death_check, philos);
	printf(SIM_START);
	pthread_mutex_unlock(philos->info->monitor);
	return (philos);
}
