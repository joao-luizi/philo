/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:39:02 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/23 13:03:34 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int argc, char **argv)
{
	t_info			*info;
	t_philo			*philos;
	pthread_mutex_t	*fork_mutex;
	int				i;

	if (argc < 5 || argc > 6)
		return (argument_number_error());
	if (!args_check(argv))
		return (inv_argument_error());
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	info_init(info, argc, argv);
	fork_mutex = fork_init(info);
	philos = philos_init(info, fork_mutex);
	threads_init(philos);
	i = -1;
	while (++i < info->number_of_philo)
		pthread_join(philos[i].tid, NULL);
	pthread_join(info->verify_death, NULL);
	printf(SIM_END);
	clean_sim(fork_mutex, philos);
	return (0);
}
