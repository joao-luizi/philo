/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:19:32 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/25 23:35:11 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

typedef struct s_table	t_table;


typedef struct s_shared
{
    unsigned int		philo_number;       // Number of philosophers
    unsigned int		time_to_die;        // Time to die in milliseconds
    unsigned int		time_to_eat;        // Time to eat in milliseconds
    unsigned int		time_to_sleep;      // Time to sleep in milliseconds
    unsigned int		time_to_think;      // Time to think in milliseconds
    int					nbr_limit_meals;    // Number of meals a philosopher must eat
    size_t				start_simulation;   // Start time of the simulation
    bool				end_simulation;     // Flag to indicate if the simulation has ended
    sem_t               *start_semaphore;
    sem_t				*table_semaphore;   // Named semaphore for table synchronization
    sem_t				*write_semaphore;   // Named semaphore for writing to output
    sem_t				*forks_semaphore;   // Named semaphore for the forks
	sem_t				*death_semaphore; 
}						t_shared;

typedef struct s_philo
{
    unsigned int		id;                 // Philosopher ID
    unsigned int		meal_counter;       // Number of meals the philosopher has eaten
    size_t				last_meal_time;     // Timestamp of the last meal
    bool				full;               // Flag to indicate if the philosopher is full
	pid_t				process_id;
    pthread_t			*monitor_thread;     // Monitor thread for this philosopher process
    sem_t				*philo_semaphore;   // Unnamed binary semaphore for process-thread synchronization
    t_shared			*shared;            // Pointer to shared resources
}						t_philo;

typedef struct s_table
{
	t_shared			*shared;
	t_philo				*philos;
	pthread_t			*parent_monitor_thread;
}						t_table;

#endif