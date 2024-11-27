# include "../inc/philo.h"


static void handle_thread_error (int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    else if (status == EAGAIN)
        error_exit(R "No resources to create another thread." RST);
    else if (status == EPERM)
        error_exit(R "The caller does not have appropriate permissions\n" RST);
    else if (status == EINVAL && opcode == CREATE)
        error_exit(R "The value specified by attr is invalid." RST);
    else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
        error_exit(R "The value specified by thread is not joinable" RST);
    else if (status == ESRCH)
        error_exit(R "No thread could be found corresponding to that specified by the given thread ID, thread" RST);
    else if (status == EDEADLK)
        error_exit(R "A deadlock was detected or the value of thread specifies the calling thread" RST);
}

void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
    if (opcode == CREATE)
        handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
    else if (opcode == JOIN)
        handle_thread_error(pthread_join(*thread, NULL), opcode);
    else if (opcode == DETACH)
        handle_thread_error(pthread_detach(*thread), opcode);
    else
        error_exit(R "Unrecognized mutex operation" RST);
}

