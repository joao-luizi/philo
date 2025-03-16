# include "../inc/philo.h"



bool all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool result;

    result = false;
    safe_mutex_handle(mutex, LOCK);
    if (*threads == philo_nbr)
        result = true;
    safe_mutex_handle(mutex, UNLOCK);
    //printf("All thread running gives %d\n", result);
    return (result);
}



