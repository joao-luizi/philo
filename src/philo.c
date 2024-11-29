# include "../inc/philo.h"
bool philo_died(t_philo *philo, t_table *table)
{
    long elapsed;
    long time_to_die;

    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
    time_to_die = table->time_to_die;

    if (elapsed > time_to_die)
        return (true);
    return (false);


}

void *monitor_dinner(void *data)
{
    t_table *table;
    int i;

    table = (t_table *)data;
    while (!all_threads_running(&table->table_mutex, &table->thread_running_count, table->philo_number))
        ;
    while (!get_bool(&table->table_mutex, &table->end_simulation))
    {
        i = 0;
        while (i < table->philo_number && !get_bool(&table->table_mutex, &table->end_simulation))
        {
            if (philo_died(table->philos + i))
            {
                set_bool(&table->table_mutex, &table->end_simulation, true);
                write_status(DEAD, table->philos + i);
            }
            i++;
        }
    }
}


static void philo_think(t_philo *philo)
{
    write_status(THINKING, philo);
}

static void philo_eat(t_philo *philo)
{
    t_table *table;

    table = get_table(NULL);
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    philo->meal_counter++;
    write_status(EATING,philo);
    custom_usleep(table->time_to_eat, table);
    if (table->nbr_limit_meals > 0 && philo->meal_counter == table->nbr_limit_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork->fork, UNLOCK);

}

void *dinner_simulation(void *data)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)data;
    table = philo->table;
    wait_all_threads(table);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    increase_long(&table->table_mutex, &table->thread_running_count);
    while (!get_bool(&table->table_mutex, &table->end_simulation))
    {
        if (philo->full)
            break ;
        write_status(SLEEPING, philo);
        custom_usleep(table->time_to_sleep, table);
    }

    return (NULL);
}

void dinner_init(t_table *table)
{
    int i;

    if (table->nbr_limit_meals == 0 || table->philo_number == 0)
        return ;
    if (table->philo_number < 2)
    {
        //todo
    }
    else
    {
        while (i < table->philo_number)
        {
            safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, &table->philos[i], CREATE);
            i++;
        }
    }

    safe_thread_handle(table->monitor, monitor_dinner, CREATE);
    table->start_simulation = get_time(MILLISECOND);
    set_bool(&table->table_mutex, &table->all_threads_ready, true);
    i = 0;
    while (i < table->philo_number)
        safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
}

int main(int argc, char **argv)
{
    (void)argv;
    t_table *table;
    if (argc == 5 || argc == 6)
    {
        table = get_table(argv);
        printf("Simulation starting with P: %ld TTD: %ld TTS %ld TTE %ld (Meals: %ld)\n",
         table->philo_number, table->time_to_die, table->time_to_sleep, table->time_to_eat, table->nbr_limit_meals);
        data_init(table);
        dinner_init(table);
    }
    else
        error_exit("Wrong input\n"\
            G"Example usage: ./philo (number of philosophers) \
(time to die) (time to eat) (time to sleep) [number of meals]\n\
./philo 5 800 200 200\n\
() - required [] - optional"RST, "main @ philo.c");
    return (0);
}