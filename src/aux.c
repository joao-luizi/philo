# include "../inc/philo.h"
void custom_usleep(long usec, t_table *table)
{
    long start;
    long elapsed;
    long remaining;

    start = get_time(MICROSECOND);
    while (1)
    {
        elapsed = get_time(MICROSECOND) - start;  
        remaining = usec - elapsed;  
        if (remaining <= 0 || get_bool(&table->table_mutex, &table->end_simulation))
            break;  
        if (remaining < 500)
        {
            while (get_time(MICROSECOND) - start < usec)
            {

            }
        }
        else 
            usleep(remaining / 2);
    }
}


long get_time(t_time_code timecode)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        error_exit("getimeofday failed.", "get_time @ aux.c");
    if (timecode == SECOND)
        return (tv.tv_sec + (tv.tv_usec / 1000000));
    else if (timecode == MILLISECOND)
        return ((tv.tv_sec  * 1000) + (tv.tv_usec / 1000));
    else if (timecode == MICROSECOND)
        return ((tv.tv_sec  * 1000000) + tv.tv_usec);
    else
        error_exit("Unknown timecode", "get_time @ aux.c");
    return(0);
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
