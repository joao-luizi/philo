/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:58:43 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/23 13:44:56 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	args_check(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) == 0)
			return (0);
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][0] == '+')
			{
				if (!(argv[i][1] >= 48 && argv[i][1] <= 57))
					return (0);
			}
			else
				if (!(argv[i][j] >= 48 && argv[i][j] <= 57))
					return (0);
		}
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long int	num;

	i = 0;
	neg = 1;
	num = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

suseconds_t	gettimems(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	log_state(int state, t_philo *philo)
{
	const char	*messages[6] = {MSG_FORK, MSG_EATING, MSG_SLEEPING,
		MSG_THINKING, MSG_SATISFIED, MSG_DEAD};

	pthread_mutex_lock(philo->info->monitor);
	if (!philo->info->finish_sim || state == DEAD)
		printf(messages[state], gettimems()
			- philo->info->start_time, philo->id);
	else if (state == SATISFIED)
		printf(messages[state], gettimems() - philo->info->start_time);
	pthread_mutex_unlock(philo->info->monitor);
}

void	in_action(t_philo *philo, suseconds_t time_to_wait)
{
	suseconds_t	start;

	start = gettimems();
	while (1)
	{
		pthread_mutex_lock(philo->info->monitor);
		if (philo->info->finish_sim)
		{
			pthread_mutex_unlock(philo->info->monitor);
			return ;
		}
		pthread_mutex_unlock(philo->info->monitor);
		if (gettimems() - start >= time_to_wait)
			return ;
		usleep(100);
	}
}
