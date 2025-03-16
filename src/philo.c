# include "../inc/philo.h"
void clean(t_table *table)
{
    if (table->console_sem)
        safe_sem_handle(table->console_sem, NULL, UNLINK);
    if (table->forks_sem)
        safe_sem_handle(table->forks_sem, NULL, UNLINK);
    if (table->end_simulation)
        safe_sem_handle(table->end_simulation, NULL, UNLINK);
    if (table->pids)
        free(table->pids);
}

t_table *get_table(char **argv)
{
    static t_table table;

    if (argv)
        parse_input(&table, argv);

    return (&table);
}

void *safe_malloc(size_t bytes)
{
    void *ret;

    ret = malloc(bytes);
    if (!ret)
        error_exit("Error on memory allocation", "safe_malloc @ aux.c");
    memset(ret,0,bytes);
    return (ret);
}

void error_exit(const char *error, char *function_name)
{
    t_table *table;
    
    table = get_table(NULL);
    if (DEBUG)
        printf(R "%s (%s)\n" RST, error, function_name);
    else
        printf(R "%s \n" RST, error);
    clean(table);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    t_table *table;
    if (argc == 5 || argc == 6)
    {
        table = get_table(argv);
        if (DEBUG)
            printf("Simulation starting with P: %ld TTD: %ld TTS %ld TTE %ld (Meals: %ld)\n",
            table->philo_number, table->time_to_die, table->time_to_sleep, table->time_to_eat, table->nbr_limit_meals);
        start_dinner(table);
        clean(table);
    }
    else
        error_exit("Wrong input\n"\
            G"Example usage: ./philo (number of philosophers) \
(time to die) (time to eat) (time to sleep) [number of meals]\n\
./philo 5 800 200 200\n\
() - required [] - optional"RST, "main @ philo.c");
    return (0);
}