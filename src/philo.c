# include "../inc/philo.h"


void *dinner_simulation(void *data)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)data;
    table = philo->table;
    wait_all_threads(table);

    while (!get_bool(&table->table_mutex, &table->end_simulation))
    {
        if (philo->full)
            break ;
        
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