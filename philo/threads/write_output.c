# include "../inc/philo.h"

void write_status(t_status status, t_philo *philo, t_table *table)
{
    long elapsed;

    if (philo->full)
        return ;
    elapsed = get_time(MILLISECOND) - table->start_simulation;
    safe_mutex_handle(&table->write_mutex, LOCK);
    if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !get_bool(&table->table_mutex,&table->end_simulation))
        write_take_fork(philo, elapsed);
    else if (status == EATING && !get_bool(&table->table_mutex,&table->end_simulation))
        write_eating(philo, elapsed);
    else if (status == SLEEPING && !get_bool(&table->table_mutex,&table->end_simulation))
        write_sleeping(philo, elapsed);
    else if (status == THINKING && !get_bool(&table->table_mutex,&table->end_simulation))
        write_thinking(philo, elapsed);
    else if (status == DEAD && !get_bool(&table->table_mutex,&table->end_simulation))
        write_dead(philo, elapsed);
    safe_mutex_handle(&table->write_mutex, UNLOCK);
}


