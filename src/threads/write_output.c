# include "../inc/philo.h"

void write_status(int id, t_status status)
{
    t_table *table;
    long elapsed;

    //have a check to see if meals eaten equals maxMeals
    table = get_table(NULL);
    sem_wait(&table->console_sem);// from the starting value 1 to 0
    elapsed = get_time(MILLISECOND) - table->start_simulation;
    if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
        write_take_fork(id, elapsed, status);//how to have philo id?
    else if (status == EATING)
        write_eating(id, elapsed);
    else if (status == SLEEPING)
        write_sleeping(id, elapsed);
    else if (status == THINKING)
        write_thinking(id, elapsed);
    else if (status == DEAD)
        write_dead(id, elapsed);
    sem_post(&table->console_sem);// from the value 0 to 1
}


