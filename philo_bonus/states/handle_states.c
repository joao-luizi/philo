# include "../inc/philo.h"


void philo_eat(t_table *table, long *last_meal, int id, long *meal_counter)
{
    if (philo_dead(table, *last_meal, table->time_to_die))
        {
            write_status(id, DEAD, table);
            exit(1);
        }
    safe_sem_handle(table->forks_sem, NULL, LOCK, table);
    write_status(id, TAKE_FIRST_FORK, table);
    if (philo_dead(table, *last_meal, table->time_to_die))
        {
            write_status(id, DEAD, table);
            exit(1);
        }
    safe_sem_handle(table->forks_sem, NULL, LOCK, table);
    write_status(id, TAKE_SECOND_FORK, table);  
    if (philo_dead(table, *last_meal, table->time_to_die))
        {
            write_status(id, DEAD, table);
            exit(1);
        }
    *last_meal = get_time(MILLISECOND, table);
    if (table->nbr_limit_meals > 0)
        (*meal_counter)++;
    if (philo_dead(table, *last_meal, table->time_to_die))
    {
        write_status(id, DEAD, table);
        exit(1);
    }
    write_status(id, EATING, table);
    custom_usleep(table->time_to_eat * 1000, table, *last_meal);
    safe_sem_handle(table->forks_sem, NULL, UNLOCK, table);
    safe_sem_handle(table->forks_sem, NULL, UNLOCK, table);
}

void philo_think(t_table *table, long *last_meal, int id)
{
    long time_to_think;
    
    write_status(id, THINKING, table);
    if (table->philo_number % 2 == 0)
        return ;
    time_to_think = (table->time_to_eat * 2) - table->time_to_sleep;   
    if (time_to_think < 0)
        time_to_think = 0;
    custom_usleep(time_to_think * 1000 * 0.5, table, *last_meal);
    
}

void philo_sleep(t_table *table, long *last_meal, int id)
{
   
    write_status(id, SLEEPING, table);
    custom_usleep(table->time_to_sleep * 1000, table, *last_meal);
}




