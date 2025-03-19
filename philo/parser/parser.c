# include "../inc/philo.h"
bool extra_errors(t_table *table)
{
    if (table->philo_number == 0)
    {
        printf(R "Invalid Input: There must be at least one philosopher\n" RST);
        return (true);
    }
    if (table->time_to_die == 0)
    {
        printf(R "Invalid Input: time to die is 0\n" RST);
        return (true);
    }
    if (table->time_to_eat == 0)
    {
        printf(R "Invalid Input: time to eat is 0\n" RST);
        return (true);
    }
    if (table->time_to_sleep == 0)
    {
        printf(R "Invalid Input: time to sleep is 0\n" RST);
        return (true);
    }
    return (false);
}

bool parse_input(t_table *table, char **argv, int argc)
{
    bool error;

    error = false;
    table->philo_number = custom_atol(argv[1], &error);
    table->time_to_die = custom_atol(argv[2], &error) * 1000;
    table->time_to_eat = custom_atol(argv[3], &error) * 1000;
    table->time_to_sleep = custom_atol(argv[4], &error) * 1000;
    table->forks = NULL;
    table->philos = NULL;
    if (argc == 6)
        table->nbr_limit_meals = custom_atol(argv[5], &error);
    else
         table->nbr_limit_meals = -1;
    if (error || extra_errors(table))
        return (false);
    return (true);
}
