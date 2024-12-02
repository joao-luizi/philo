# include "../inc/philo.h"


static void handle_thread_error (int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    else if (status == EAGAIN)
        error_exit("No resources to create another thread." , "handle_thread_error @ threads/error_handler.c");
    else if (status == EPERM)
        error_exit( "The caller does not have appropriate permissions\n" , "handle_thread_error @ threads/error_handler.c");
    else if (status == EINVAL && opcode == CREATE)
        error_exit( "The value specified by attr is invalid." , "handle_thread_error @ threads/error_handler.c");
    else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
        error_exit( "The value specified by thread is not joinable" , "handle_thread_error @ threads/error_handler.c");
    else if (status == ESRCH)
        error_exit( "No thread could be found corresponding to that specified by the given thread ID, thread" , "handle_thread_error @ threads/error_handler.c");
    else if (status == EDEADLK)
        error_exit("A deadlock was detected or the value of thread specifies the calling thread", "handle_thread_error @ threads/error_handler.c");
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
        error_exit("Unrecognized mutex operation", "safe_thread_handle @ threads/error_handler.c");
}

