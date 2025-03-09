# include "../inc/philo.h"
void clean(t_state *state)
{
    t_philo *philo;
    int i;

    i = 0;
    while (i < state->config->number_of_philos)
    {
        philo = state->philos + i;
        safe_mutex_handle(&philo->philo_mutex, DESTROY);
        i++;
    }
    safe_mutex_handle(&state->console_mutex, DESTROY);
    safe_mutex_handle(&state->state_mutex, DESTROY);
    if (state->forks)
        free(state->forks);
    if (state->philos)
        free(state->philos);
}

t_state *get_state(t_config* config)
{
    static t_state state;

    if (config)
        state.config = config;
    return (&state);
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
    t_state *state;

    state = get_state(NULL);
    if (DEBUG)
        printf(R "%s (%s)\n" RST, error, function_name);
    else
        printf(R "%s \n" RST, error);
    clean(state);
    exit(EXIT_FAILURE);
}
void display_help_msg()
{
    error_exit("Wrong input\n"G"Example usage: ./philo (number of philosophers) \
    (time to die) (time to eat) (time to sleep) [number of meals]\n\
    ./philo 5 800 200 200\n\
    () - required [] - optional"RST, "main @ philo.c");

}
int main(int argc, char **argv)
{
    
    t_state *state;
    t_config config;

    if (argc == 5 || argc == 6)
    {
        parse_input(&config, argv);
        state = get_state(&config);
        //print_config(&config);
        state_init(state);
        philo_init(state);
        debug_state(state);
        dinner_init(state);
        //clean(state);
    }
    else
        display_help_msg();
    return (0);
}