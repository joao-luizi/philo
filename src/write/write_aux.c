# include "../inc/philo.h"

void write_dead(int id, long elapsed)
{
    if (DEBUG)
        printf(W "%-6ld" RST " %d is dead.\n", elapsed, id);
    else
        printf(W "%-6ld" RST " %d is dead\n", elapsed, id);
}

void write_thinking(int id, long elapsed)
{
    if (DEBUG)
        printf(W "%-6ld" RST " %d is thinking.\n", elapsed, id);
    else
        printf(W "%-6ld" RST " %d is thinking\n", elapsed, id);
}

void write_sleeping(int id, long elapsed)
{
    if (DEBUG)
        printf(W "%-6ld" RST " %d is sleeping.\n", elapsed, id);
    else
        printf(W "%-6ld" RST " %d is sleeping\n", elapsed, id);
}

void write_eating(int id, long elapsed)
{
    if (DEBUG)
        printf(W "%-6ld" RST " %d is eating.\n", elapsed, id);
    else
        printf(W "%-6ld" RST " %d is eating.\n", elapsed, id);
}

void write_take_fork(int id, long elapsed, t_status status)
{
    if (DEBUG)
    {
        if (status == TAKE_FIRST_FORK)
            printf(W "%-6ld" RST " %d has taken the first fork.\n", elapsed, id);
        else
            printf(W "%-6ld" RST " %d has taken the second fork.\n", elapsed, id);    
    }
    else
        printf(W "%-6ld" RST " %d has taken a fork\n", elapsed, id);
}




