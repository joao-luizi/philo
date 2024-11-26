# include "../inc/philo.h"
void *safe_malloc(size_t bytes)
{
    void *ret;

    ret = malloc(bytes);
    if (!ret)
        error_exit(R "Error on memory allocation" RST);
    memset(ret,0,bytes);
    return (ret);
}

void error_exit(const char *error)
{
    printf(R "%s\n" RST, error);
    exit(EXIT_FAILURE);
}

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

static void handle_thread_error (int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    else if (status == EAGAIN)
        error_exit(R "No resources to create another thread." RST);
    else if (status == EPERM)
        error_exit(R "" RST);
    else if (status == EINVAL && opcode == CREATE)
        error_exit(R "" RST);
    else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
        error_exit(R "" RST);
    else if (status == ESRCH)
        error_exit(R "" RST);
    else if (status == EDEADLK)
        error_exit(R "" RST);
}

void safe_thread_handle(pthread_t *thread, void *(*foo), void *data, t_opcode opcode)
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

