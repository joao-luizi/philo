# include "inc/philo.h"
void clean(t_table *table)
{
    t_philo *philo;
    t_fork *fork;
    int i;

    i = 0;
    while (i < table->philo_number)
    {
        philo = table->philos + i;
        fork = table->forks + i;
        safe_mutex_handle(&philo->philo_mutex, DESTROY);
        safe_mutex_handle(&fork->fork, DESTROY);
        i++;
    }
    safe_mutex_handle(&table->write_mutex, DESTROY);
    safe_mutex_handle(&table->table_mutex, DESTROY);
    if (table->forks)
        free(table->forks);
    if (table->philos)
        free(table->philos);
}



void *safe_malloc(size_t bytes)
{
    void *ret;

    ret = malloc(bytes);
    if (!ret)
    {
        printf(R "Error on memory allocation\n" RST);
        return (NULL);
    }
    memset(ret,0,bytes);
    return (ret);
}


int main(int argc, char **argv)
{
    t_table table;
    bool error;

    error = false;
    if (argc == 5 || argc == 6)
    {
        if (!parse_input(&table, argv, argc))
            return (1);
        error = !table_init(&table);
        if (!error)
            error = !philo_init(&table);
        if (!error)
            error = !dinner_init(&table);
        clean(&table);
    }
    else
    {
        printf(R "Wrong input\n"G"Example usage: ./philo (number of philosophers) (time to die) (time to eat) \
            (time to sleep) [number of meals]\n ./philo 5 800 200 200\n() - required [] - optional"RST);
        return (1);
    }
    return (0);
}
