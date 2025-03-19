# include "../inc/philo.h"

bool philo_full(long meal_counter, long nbr_limit_meals)
{
    if (nbr_limit_meals > 0)    
        return (meal_counter >= nbr_limit_meals);
    return (false);
}

bool philo_dead(t_table *table, long last_meal, long time_to_die)
{
    long time = get_time(MILLISECOND, table);
    long elapsed = time - last_meal;
   
    return (elapsed >= time_to_die);
}


void write_status(int id, t_status status, t_table *table)
{
    long elapsed;
    safe_sem_handle(table->console_sem, NULL, LOCK, table);
    elapsed = get_time(MILLISECOND, table) - table->start_simulation;
    if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
        write_take_fork(id, elapsed, status);
    else if (status == EATING)
        write_eating(id, elapsed);
    else if (status == SLEEPING)
        write_sleeping(id, elapsed);
    else if (status == THINKING)
        write_thinking(id, elapsed);
    else if (status == DEAD)
        write_dead(id, elapsed);
    safe_sem_handle(table->console_sem, NULL, UNLOCK, table);
}


