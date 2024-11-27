
# include "../inc/philo.h"

static void handle_mutex_error (int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
        error_exit(R "The value specified by mutex is invalid." RST);
    else if (status == EINVAL && opcode == INIT )
        error_exit(R "The value specified by attr is invalid." RST);
    else if (status == EDEADLK)
        error_exit(R "A deadlock would occur if the thread blocked waiting for mutex." RST);
    else if (status == EPERM)
        error_exit(R "The current thread does not hold a lock on mutex." RST);
    else if (status == ENOMEM)
        error_exit(R "The process cannot allocate enough memory to create another mutex." RST);
    else if (status == EBUSY)
        error_exit(R "Mutex is locked." RST);
}

void safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
    if (opcode == LOCK)
        handle_mutex_error(pthread_mutex_lock(mutex), opcode);
    else if (opcode == UNLOCK)
        handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
    else if (opcode == INIT)
        handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
    else if (opcode == DESTROY)
        handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
    else
        error_exit(R "Unrecognized mutex operation" RST);
}
