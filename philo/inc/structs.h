/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:19:32 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/25 12:32:29 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t		*fork;
	int					fork_id;

}						t_fork;

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
	pthread_mutex_t		*table_mutex;
	pthread_mutex_t		*write_mutex;
}						t_shared;

typedef struct s_philo
{
	unsigned int		id;
	unsigned int		meal_counter;
	size_t				last_meal_time;
	bool				full;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_mutex_t		*philo_mutex;
	pthread_t			*thread_id;
	t_shared			*shared;
}						t_philo;

typedef struct s_table
{
	t_shared			*shared;
	pthread_t			*monitor;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

#endif