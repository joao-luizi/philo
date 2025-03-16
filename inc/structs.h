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
    bool         full;
    t_fork      *first_fork;
    t_fork      *second_fork;
    t_mtx       philo_mutex;
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
    pid_t   *pids;
    sem_t   forks_sem;
    sem_t   console_sem;
    sem_t   end_simulation;

}t_table;

typedef struct s_pid_list
{
    pid_t   pid;
    int     id;
    struct s_pid_list *next;

}t_pid_list;

#endif