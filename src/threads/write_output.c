# include "../inc/philo.h"

void write_status(t_status status, t_philo *philo)
{
    t_state *state;
    long elapsed;

    state = get_state(NULL);
    if (is_philo_full(philo, state->config))
        return ;
    elapsed = get_time(MILLISECOND) - state->simulation_start_time;
    //printf("Start is %ld elapsed is %ld\n", table->start_simulation, elapsed);
    safe_mutex_handle(&state->console_mutex, LOCK);
    if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !get_bool(&state->state_mutex, &state->simulation_finished))
        write_take_fork(philo, elapsed, status);
    else if (status == EATING && !get_bool(&state->state_mutex, &state->simulation_finished))
        write_eating(philo, elapsed);
    else if (status == SLEEPING && !get_bool(&state->state_mutex, &state->simulation_finished))
        write_sleeping(philo, elapsed);
    else if (status == THINKING && !get_bool(&state->state_mutex, &state->simulation_finished))
        write_thinking(philo, elapsed);
    else if (status == DEAD && !get_bool(&state->state_mutex, &state->simulation_finished))
        write_dead(philo, elapsed);
    safe_mutex_handle(&state->console_mutex, UNLOCK);
}


