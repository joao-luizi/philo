# include "../inc/philo.h"

void *lone_philo(void * data)
{
    t_philo *philo;
    t_state *state;

    state = get_state(NULL);
    philo = (t_philo *)data;
    while (philo->last_meal_time < 0)
        philo->last_meal_time = get_long(&state->state_mutex, &state->simulation_start_time);
    printf("Simulation Start Time: %ld Philo Start Time: %ld\n", 
        get_long(&state->state_mutex, &state->simulation_start_time), philo->last_meal_time); //they should be the same
    increase_long(&state->state_mutex, &state->running_threads);
    write_status(TAKE_FIRST_FORK, philo);
    while (!get_bool(&state->state_mutex, &state->simulation_finished))
    {
        if (philo_died(philo, state))
        {
            write_status(DEAD, philo);
            set_bool(&state->state_mutex, &state->simulation_finished, true);
            break;
        }
        usleep(30);
    }
    return (NULL);
}
void de_sync_philos(t_philo *philo, t_state *state)
{


    if (state->config->number_of_philos % 2 == 0)
    {
        if (philo->id % 2 == 0)
            custom_usleep(30000, state);
    }
    else
    {
        if (philo->id % 2 == 0)
            philo_think(philo, state);;
    }
}
void *dinner_simulation(void *data)
{
    t_philo *philo;
    t_state *state;

    philo = (t_philo *)data;
    state = get_state(NULL);
    wait_all_threads(state);
    //set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    philo->last_meal_time = get_time(MILLISECOND);
    increase_long(&state->state_mutex, &state->running_threads);
    de_sync_philos(philo, state);
    while (!get_bool(&state->state_mutex, &state->simulation_finished))
    {
        if (is_philo_full(philo, state->config))
            break;
        philo_eat(philo);
        write_status(SLEEPING, philo);
        //printf("Im going to sleep for %ld\n", table->time_to_sleep);
        custom_usleep(state->config->time_to_sleep * 1000, state);
        philo_think(philo, state);
    }

    return (NULL);
}

void dinner_init(t_state *state)
{
    int i;

    if (state->config->max_meals == 0 || state->config->number_of_philos == 0)
        return ;
    if (state->config->number_of_philos < 2)
        safe_thread_handle(&state->philos[0].thread_id, lone_philo, &state->philos[0], CREATE);
    else
    {
        i = 0;
        while (i < state->config->number_of_philos)
        {
            safe_thread_handle(&state->philos[i].thread_id, dinner_simulation, &state->philos[i], CREATE);
            i++;
        }
    }
    state->simulation_start_time = get_time(MILLISECOND); //this replaces setting the boll all_threads_ready
    //set_bool(&state->state_mutex, &state->all_threads_ready, true);
    i = 0;
    while (i < state->config->number_of_philos)
    {
        safe_thread_handle(&state->philos[i].thread_id, NULL, NULL, JOIN);
        i++;
    }
    
}

void state_init(t_state *state)
{
	int i;

	state->simulation_finished = false;
	//table->all_threads_ready = false;
    state->simulation_start_time = -1; // this will be read by the threads and as long as is less than zero they will not run the simulation
    state->running_threads = 0;
	state->philos = safe_malloc(sizeof(t_philo) * state->config->number_of_philos);
	safe_mutex_handle(&state->state_mutex, INIT);
	state->forks = safe_malloc(sizeof(t_fork) * state->config->number_of_philos);
	i = 0;
	while (i < state->config->number_of_philos)
	{
		safe_mutex_handle(&state->forks[i].fork, INIT);
		state->forks[i].fork_id = i;
		i++;
	}
}