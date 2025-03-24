/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:19:32 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/24 14:47:47 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;

}						t_fork;
typedef struct s_philo
{
	int					id;
	unsigned int				meal_counter;
	unsigned int				last_meal_time;
	bool				full;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_mtx				philo_mutex;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	unsigned int				philo_number;
	unsigned int				time_to_die;
	unsigned int				time_to_eat;
	unsigned int				time_to_sleep;
	unsigned int				time_to_think;
	int				nbr_limit_meals;
	unsigned int				start_simulation;
	bool				end_simulation;
	bool				all_threads_ready;
	unsigned int				thread_running_count;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;

}						t_table;

#endif