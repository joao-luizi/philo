/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:19:32 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/26 13:40:17 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

typedef struct s_table	t_table;

typedef struct s_shared
{
	unsigned int		philo_number;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		time_to_think;
	int					nbr_limit_meals;
	size_t				start_simulation;
	bool				end_simulation;
	sem_t				*start_semaphore;
	sem_t				*table_semaphore;
	sem_t				*write_semaphore;
	sem_t				*forks_semaphore;
	sem_t				*death_semaphore;
}						t_shared;

typedef struct s_philo
{
	unsigned int		id;
	unsigned int		meal_counter;
	size_t				last_meal_time;
	bool				full;
	pid_t				process_id;
	pthread_t			*monitor_thread;
	sem_t				*philo_semaphore;

	t_shared			*shared;
}						t_philo;

typedef struct s_table
{
	t_shared			*shared;
	t_philo				*philos;
	pthread_t			*parent_monitor_thread;
}						t_table;

#endif