# include "../inc/philo.h"

void write_dead(t_philo *philo, long elapsed)
{
    if (DEBUG)
        printf(W "%-6ld" RST " %d is dead.\n", elapsed, philo->id);
    else
        printf(W "%-6ld" RST " %d is dead.\n", elapsed, philo->id);
}

void write_thinking(t_philo *philo, long elapsed)
{
    if (DEBUG)
        printf(W "%-6ld" RST " %d is thinking.\n", elapsed, philo->id);
    else
        printf(W "%-6ld" RST " %d is thinking.\n", elapsed, philo->id);
}

void write_sleeping(t_philo *philo, long elapsed)
{
    if (DEBUG)
        printf(W "%-6ld" RST " %d is sleeping.\n", elapsed, philo->id);
    else
        printf(W "%-6ld" RST " %d is sleeping.\n", elapsed, philo->id);
}

void write_eating(t_philo *philo, long elapsed)
{
    if (DEBUG)
        printf(W "%-6ld" RST " %d is eating (Meals: %ld).\n", elapsed, philo->id, philo->meal_counter);
    else
        printf(W "%-6ld" RST " %d is eating.\n", elapsed, philo->id);
}

void write_take_fork(t_philo *philo, long elapsed, t_status status)
{
    if (DEBUG)
    {
        if (status == TAKE_FIRST_FORK)
            printf(W "%-6ld" RST " %d has taken the first fork (%d).\n", elapsed, philo->id, philo->first_fork->fork_id);
        else
            printf(W "%-6ld" RST " %d has taken the second fork (%d).\n", elapsed, philo->id, philo->second_fork->fork_id);    
    }
    else
        printf(W "%-6ld" RST " %d has taken a fork.\n", elapsed, philo->id);
}




