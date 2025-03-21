# ifndef STRUCTS_H
#define STRUCTS_H

#include "defines.h"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	long				meal_counter;
	long				last_meal_time;
	bool				full;
	bool				dead;
	sem_t				*philo_semaphore;
    pid_t				process_id; 
    pthread_t			monitor;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				philo_number;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_to_think;
	long				nbr_limit_meals;
	long				start_simulation;
	bool				end_simulation;
	long				process_running_count;
	pthread_t 			death_thread;
	sem_t               *start_semaphore;
    sem_t				*table_semaphore;    
    sem_t				*write_semaphore;    
    sem_t				*forks;   
	sem_t 				*death_semaphore;
    t_philo				*philos;           
}						t_table;







#endif