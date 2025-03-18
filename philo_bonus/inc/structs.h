# ifndef STRUCTS_H
#define STRUCTS_H

#include "defines.h"

typedef struct s_pid_list
{
    pid_t   pid;
    int     id;
    struct s_pid_list *next;

}t_pid_list;

typedef struct s_table
{
    long	    philo_number;
    long	    time_to_die;
    long	    time_to_eat;
    long	    time_to_sleep;
    long	    nbr_limit_meals;
    long	    start_simulation;
    t_pid_list  *pids;
    sem_t       *forks_sem;
    sem_t       *console_sem;
    sem_t       *end_simulation;

}t_table;



#endif