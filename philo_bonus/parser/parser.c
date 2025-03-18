# include "../inc/philo.h"

void parse_input(t_table *table, char **argv)
{
    table->console_sem = NULL;
    table->forks_sem = NULL;
    table->end_simulation = NULL;
    table->pids = NULL;
    table->philo_number = custom_atol(argv[1]);
    if (table->philo_number == 0)
        error_exit("Input Error: There must be at least one philosopher", "parse_input @ parser/parser.c");
    table->time_to_die = custom_atol(argv[2]);
    if (table->time_to_die < 60)
        error_exit( "Input Error: time to die below 60ms" , "parse_input @ parser/parser.c");
    table->time_to_eat = custom_atol(argv[3]);
    if (table->time_to_eat < 60)
        error_exit( "Input Error: time to eat below 60ms" , "parse_input @ parser/parser.c");
    table->time_to_sleep = custom_atol(argv[4]);
    if (table->time_to_sleep < 60)
        error_exit( "Input Error: time to sleep below 60ms" , "parse_input @ parser/parser.c");
    if (argv[5])
        table->nbr_limit_meals = custom_atol(argv[5]);
    else
         table->nbr_limit_meals = -1;
}
