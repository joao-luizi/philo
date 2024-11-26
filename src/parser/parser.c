# include "../inc/philo.h"

void parse_input(t_table *table, char **argv)
{
    table->philo_number = custom_atol(argv[1]);
    if (table->philo_number == 0)
        error_exit(R "Input Error: There must be at least one philosopher" RST);
    table->time_to_die = custom_atol(argv[2]) * 1000;
    if (table->time_to_die < 60000)
        error_exit(R "Input Error: time to die below 60ms" RST);
    table->time_to_eat = custom_atol(argv[3]) * 1000;
    if (table->time_to_eat < 60000)
        error_exit(R "Input Error: time to eat below 60ms" RST);
    table->time_to_sleep = custom_atol(argv[4]) * 1000;
    if (table->time_to_sleep < 60000)
        error_exit(R "Input Error: time to sleep below 60ms" RST);
    if (argv[5])
        table->nbr_limit_meals = custom_atol(argv[5]);
    else
         table->nbr_limit_meals = -1;
}
