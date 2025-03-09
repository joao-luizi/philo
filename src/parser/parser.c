# include "../inc/philo.h"

void parse_input(t_config *config, char **argv)
{
    config->number_of_philos = custom_atol(argv[1]);
    if (config->number_of_philos == 0)
        error_exit("Input Error: There must be at least one philosopher", "parse_input @ parser/parser.c");
    if(config->number_of_philos > 399)
    error_exit("Input Error: Maximum supported philos is 399", "parse_input @ parser/parser.c");
    config->time_to_die = custom_atol(argv[2]);
    if (config->time_to_die < 60000)
        error_exit( "Input Error: time to die below 60ms" , "parse_input @ parser/parser.c");
    config->time_to_eat = custom_atol(argv[3]);
    if (config->time_to_eat < 60000)
        error_exit( "Input Error: time to eat below 60ms" , "parse_input @ parser/parser.c");
    config->time_to_sleep = custom_atol(argv[4]);
    if (config->time_to_sleep < 60000)
        error_exit( "Input Error: time to sleep below 60ms" , "parse_input @ parser/parser.c");
    if (argv[5])
    {
        config->max_meals = custom_atol(argv[5]);
        if (config->max_meals < 0)
            error_exit("Input Error: max_meals must be a positive number or omitted", "parse_input @ parser/parser.c");
    }
    else
    {
        config->max_meals = -1;
    }
}
