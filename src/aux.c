# include "../inc/philo.h"

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
    int i;
    
    i = 0;
    table = get_table(NULL);
    while (i < table->philo_number)
    {
       i++;
    }
    if (DEBUG)
        printf(R "%s (%s)\n" RST, error, function_name);
    else
        printf(R "%s \n" RST, error);
    exit(EXIT_FAILURE);
}
