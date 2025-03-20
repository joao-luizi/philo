# ifndef STRUCTS_H
#define STRUCTS_H

#include "defines.h"

typedef struct s_table	t_table;

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
	bool				all_processes_ready;
	long				process_running_count;
    sem_t				*table_semaphore;    
    sem_t				*write_semaphore;    
    sem_t				*forks;              
}						t_table;

typedef struct s_philo
{
	int					id;
	long				meal_counter;
	long				last_meal_time;
	bool				full;
	sem_t				*philo_semaphore;
    pid_t				process_id; 
    pthread_t			monitor;
	t_table				*table;
}						t_philo;





#endif