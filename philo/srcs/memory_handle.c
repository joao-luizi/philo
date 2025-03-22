/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:29:36 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/16 14:47:35 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	clean_sim(pthread_mutex_t *fork_mutex, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->info->number_of_philo)
		pthread_mutex_destroy(&fork_mutex[i]);
	pthread_mutex_destroy(philos->info->monitor);
	free(philos->info->monitor);
	free(fork_mutex);
	free(philos->info);
	free(philos);
}
