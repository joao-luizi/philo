# include "../inc/philo.h"

void write_status(t_status status, t_philo *philo)
{
    t_table *table;
    long elapsed;
    bool simulation_ended;

    if (philo->full)
        return ;
    table = get_table(NULL);
    elapsed = get_time(MILLISECOND) - table->start_simulation;
    simulation_ended = get_bool(&table->table_mutex,&table->end_simulation);
    safe_mutex_handle(&table->write_mutex, LOCK);
    if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !simulation_ended)
        write_take_fork(philo, elapsed, status);
    else if (status == EATING && !simulation_ended)
        write_eating(philo, elapsed);
    else if (status == SLEEPING && !simulation_ended)
        write_sleeping(philo, elapsed);
    else if (status == THINKING && !simulation_ended)
        write_thinking(philo, elapsed);
    else if (status == DEAD && !simulation_ended)
        write_dead(philo, elapsed);
    safe_mutex_handle(&table->write_mutex, UNLOCK);
}


