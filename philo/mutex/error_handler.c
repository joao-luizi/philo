
# include "../inc/philo.h"

static void handle_mutex_error (int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
        error_exit("The value specified by mutex is invalid." , "handle_mutex_error @ mutes/error_handler.c");
    else if (status == EINVAL && opcode == INIT )
        error_exit("The value specified by attr is invalid." , "handle_mutex_error @ mutes/error_handler.c");
    else if (status == EDEADLK)
        error_exit("A deadlock would occur if the thread blocked waiting for mutex." , "handle_mutex_error @ mutes/error_handler.c");
    else if (status == EPERM)
        error_exit("The current thread does not hold a lock on mutex." , "handle_mutex_error @ mutes/error_handler.c");
    else if (status == ENOMEM)
        error_exit("The process cannot allocate enough memory to create another mutex.", "handle_mutex_error @ mutes/error_handler.c");
    else if (status == EBUSY)
        error_exit("Mutex is locked." , "handle_mutex_error @ mutes/error_handler.c");
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
        error_exit("Unrecognized mutex operation", "safe_mutex_handle @ mutes/error_handler.c");
}
