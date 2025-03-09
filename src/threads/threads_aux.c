# include "../inc/philo.h"

void wait_all_threads(t_state *state)
{
    while (get_long(&state->state_mutex, &state->simulation_start_time) < 0)
        ;
    //while(!get_bool(&table->table_mutex, &table->all_threads_ready))
    //    ;
}

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



