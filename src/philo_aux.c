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
void debug_state(t_state *state)
{
    int i;

    printf("\n===== DEBUG STATE =====\n");
    
    // Print Config Details
    printf("Philosophers: %ld | Time to Die: %ld | Time to Eat: %ld | Time to Sleep: %ld | Max Meals: %ld\n",
           state->config->number_of_philos, state->config->time_to_die, 
           state->config->time_to_eat, state->config->time_to_sleep, 
           state->config->max_meals);
    
    // Print State Info
    printf("Simulation Start: %ld | Finished: %d | Running Threads: %ld | Dead Philosophers: %ld\n",
           state->simulation_start_time, state->simulation_finished, 
           state->running_threads, state->dead_philos);
    
    // Print Forks Info
    printf("\nForks:\n");
    for (i = 0; i < state->config->number_of_philos; i++)
        printf("Fork[%d]: ID = %d\n", i, state->forks[i].fork_id);

    // Print Philosophers Info
    printf("\nPhilosophers:\n");
    for (i = 0; i < state->config->number_of_philos; i++)
    {
        t_philo *philo = &state->philos[i];
        printf("Philo[%d]: ID = %d | Meals: %ld | Last Meal Time: %ld | Forks: [%d, %d]\n",
               i, philo->id, philo->meal_counter, philo->last_meal_time, 
               philo->first_fork->fork_id, philo->second_fork->fork_id);
    }
    printf("=======================\n\n");
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

