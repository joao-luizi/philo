# include "../inc/philo.h"


void philo_eat(t_table *table, long *last_meal, int id, long *meal_counter)
{
    safe_sem_handle(table->forks_sem, NULL, LOCK, table);
    write_status(id, TAKE_FIRST_FORK, table);
    safe_sem_handle(table->forks_sem, NULL, LOCK, table);
    write_status(id, TAKE_SECOND_FORK, table);  
    *last_meal = get_time(MILLISECOND, table);
    if (table->nbr_limit_meals > 0)
        (*meal_counter)++;
    write_status(id, EATING, table);
    while (get_time(MILLISECOND, table) < *last_meal + table->time_to_eat)
    {
        if (philo_dead(table, *last_meal, table->time_to_die))
        {
            safe_sem_handle(table->forks_sem, NULL, UNLOCK, table);
            safe_sem_handle(table->forks_sem, NULL, UNLOCK, table);
            exit(1);
        }
        custom_usleep(10, table);
    }
    safe_sem_handle(table->forks_sem, NULL, UNLOCK, table);
    safe_sem_handle(table->forks_sem, NULL, UNLOCK, table);
}

void philo_think(t_table *table, long *last_meal, int id)
{
    long start = get_time(MILLISECOND, table);
    long time_to_think = (table ->time_to_die - table->time_to_eat - table->time_to_sleep) * 0.5;
    if (time_to_think < 0)
        time_to_think = 0;
    long end = start + time_to_think;
    write_status(id, THINKING, table);
    while (get_time(MILLISECOND, table) < end)
    {
        if (philo_dead(table, *last_meal, table->time_to_die))
            exit(1);
        custom_usleep(10, table);
    }
}

void philo_sleep(t_table *table, long *last_meal, int id)
{
    long start = get_time(MILLISECOND, table);
    long end = start + table->time_to_sleep;
    write_status(id, SLEEPING, table);
    while (get_time(MILLISECOND, table) < end)
    {
        if (philo_dead(table, *last_meal, table->time_to_die))
            exit(1);
        custom_usleep(10, table);
    }
}




