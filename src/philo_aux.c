# include "../inc/philo.h"
void custom_usleep(long usec, t_state *state)
{
    long start;
    long elapsed;
    long remaining;

    start = get_time(MICROSECOND);
    while (1)
    {
        elapsed = get_time(MICROSECOND) - start;  
        remaining = usec - elapsed;  
        //printf("Custom u elapsed is %ld remaining is %ld\n", elapsed, remaining);
        if (remaining <= 0 || get_bool(&state->state_mutex, &state->simulation_finished))
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


void print_config(const t_config *config)
{
    printf("Configuration:\n");
    printf("Number of Philosophers: %ld\n", config->number_of_philos);
    printf("Time to Die: %ld ms\n", config->time_to_die);
    printf("Time to Eat: %ld ms\n", config->time_to_eat);
    printf("Time to Sleep: %ld ms\n", config->time_to_sleep);
    
    if (config->max_meals == -1)
        printf("Max Meals: No Limit\n");
    else
        printf("Max Meals: %ld\n", config->max_meals);
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

