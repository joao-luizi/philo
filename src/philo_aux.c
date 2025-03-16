# include "../inc/philo.h"
void custom_usleep(long usec)
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
        if (remaining <= 0)
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

