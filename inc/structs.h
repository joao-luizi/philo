# ifndef STRUCTS_H
#define STRUCTS_H

#include "defines.h"

typedef pthread_mutex_t t_mtx;
typedef struct s_table t_table;

typedef struct s_fork
{
    t_mtx   fork;
    int     fork_id;

}t_fork;
typedef struct s_philo
{
    int         id;
    long        meal_counter;
    long        last_meal_time;
    int         full;
    t_fork      *first_fork;
    t_fork      *second_fork;
    pthread_t   thread_id;
	t_table		*table;
}   t_philo;

typedef struct s_table
{
    long	philo_number;
    long	time_to_die;
    long	time_to_eat;
    long	time_to_sleep;
    long	nbr_limit_meals;
    long	start_simulation;
    bool	end_simulation;
    bool    all_threads_ready;
    t_mtx   table_mutex;
	t_fork	*forks;
	t_philo	*philos;

}t_table;

#endif