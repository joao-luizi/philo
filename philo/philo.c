# include "inc/philo.h"

/*
5 800 200 200
no one should die
5 600 150 150
no one should die
4 410 200 200
no one should die
100 800 200 200
no one should die
105 800 200 200
no one should die
200 800 200 200
no one should die

1 800 200 200
a philo should die
4 310 200 100
a philo should die
4 200 205 200
a philo should die
5 800 200 200 7
no one should die, simulation should stop after 7 eats
4 410 200 200 10
no one should die, simulation should stop after 10 eats
-5 600 200 200
should error and not run (no crashing)
4 -5 200 200
should error and not run (no crashing)
4 600 -5 200
should error and not run (no crashing)
4 600 200 -5
should error and not run (no crashing)
4 600 200 200 -5
should error and not run (no crashing)
*/
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
