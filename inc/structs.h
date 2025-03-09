# ifndef STRUCTS_H
#define STRUCTS_H

#include "defines.h"

typedef pthread_mutex_t t_mtx;

typedef struct s_config
{
    long   number_of_philos;
    long   time_to_die;
    long   time_to_eat;
    long   time_to_sleep;
    long   max_meals;

}t_config;

typedef struct s_fork
{
    t_mtx   fork;
    int     fork_id;

}t_fork;

typedef struct s_philo
{
    int             id;
    pthread_t       thread_id;
    long            meal_counter;
    long            last_meal_time;
    t_fork          *first_fork;
    t_fork          *second_fork;
    t_mtx           philo_mutex;
}   t_philo;

typedef struct s_state
{
    t_config        *config;
    long            simulation_start_time;
    bool            simulation_finished;
    long            running_threads;
    long    dead_philos;//when a philo dies i lock the state mutex I check the dead_philos variable if it is 0 i anounce the death of the philo and increase the dead_philos variable. 
    t_mtx           state_mutex; //this is a pthread_mutex_t
    t_mtx           console_mutex; // this is a pthread_mutex_t to LOCK / UNLOCK writing to the console by philosophers
	t_fork	        *forks;//this is a strctu with a pthread_mutex_t and an int (ID)
	t_philo	        *philos; //

}t_state;



#endif