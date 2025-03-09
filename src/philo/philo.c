# include "../inc/philo.h"
bool is_philo_full(t_philo *philo, t_config *config)
{
    return (config->max_meals > 0 && philo->meal_counter >= config->max_meals);
}

bool philo_died(t_philo *philo, t_state *state)
{
    long elapsed;
    long time_to_die;
    long last_meal_time;

    if (is_philo_full(philo, state->config))
        return (false);
    
    last_meal_time = philo->last_meal_time; //MILLISECONDS
    elapsed = get_time(MILLISECOND) - last_meal_time; // SHOULD BE MILLISENDS
    time_to_die = state->config->time_to_die;

    printf("Philosopher %d - Last meal time: %ld ms, Elapsed time: %ld ms, Time to die: %ld ms\n", 
        philo->id, last_meal_time, elapsed, time_to_die);
        
    if (elapsed > time_to_die)
        return (true);
    return (false);

}

void philo_think(t_philo *philo, t_state *state)
{
    long time_to_think;

    write_status(THINKING, philo);
    if (state->config->number_of_philos % 2 == 0)
        return ;
    time_to_think = (state->config->time_to_eat * 2) - state->config->time_to_sleep;   
    if (time_to_think < 0)
        time_to_think = 0;
    custom_usleep(time_to_think * 1000 * 0.4, state);

}

void philo_eat(t_philo *philo)
{
    t_state *state;

    state = get_state(NULL);
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo);
    philo->last_meal_time = get_time(MILLISECOND);
    philo->meal_counter++;
    write_status(EATING,philo);
    custom_usleep(state->config->time_to_eat * 1000, state);
    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork->fork, UNLOCK);

}

static void assign_forks(t_philo *philo, t_state *state, int philo_pos)
{
    int philo_number;
    t_fork *forks;

    forks = state->forks;
    philo_number = state->config->number_of_philos;
    philo->first_fork = &forks[(philo_pos + 1) % philo_number];
    philo->second_fork = &forks[philo_pos];
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &forks[philo_pos];
        philo->second_fork= &forks[(philo_pos + 1) % philo_number];
    }
    
}

void philo_init(t_state *state)
{
    int i;
    t_philo *philo;

    i = 0;
    while (i <state->config->number_of_philos)
    {
        philo = state->philos + i;
        philo->id = i + 1;
        philo->meal_counter = 0;
        philo->last_meal_time = -1;
        //safe_mutex_handle(&philo->philo_mutex, INIT); --the intention is to not use a mutex
        assign_forks(philo, state, i);
        i++;
    }
}