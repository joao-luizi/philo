
# include "../inc/philo.h"

static void handle_sem_error_unlink(int status, t_table *table)
{
    char ref[] = "handle_sem_error_create @ semaphores/error_handler.c";
    if (status == EACCES)
        error_exit("The caller does not have permission to unlink this semaphore.", ref, table);
    else if (status == ENAMETOOLONG)
        error_exit("The semaphore name is too long.", ref, table);
    else if (status == ENOENT)
        error_exit("There is no semaphore with the given name.", ref, table);
}

static void handle_sem_error_create(int status, t_table *table)
{
    char ref[] = "handle_sem_error_create @ semaphores/error_handler.c";
    if (status == 0)
        return;
    if (status == EACCES)
        error_exit("The semaphore exists, but the caller does not have permission to open it.", ref, table);
    else if (status == EEXIST)
        error_exit("Both O_CREAT and O_EXCL were specified, but a semaphore with this name already exists.", ref, table);
    else if (status == EINVAL)
        error_exit("Invalid semaphore name format or value is greater than SEM_VALUE_MAX.", ref, table);
    else if (status == EMFILE)
        error_exit("The per-process limit on open file descriptors has been reached.", ref, table);
    else if (status == ENAMETOOLONG)
        error_exit("The semaphore name is too long.", ref, table);
    else if (status == ENFILE)
        error_exit("The system-wide limit on total open files has been reached.", ref, table);
    else if (status == ENOENT)
        error_exit("The semaphore does not exist, and O_CREAT was not specified, or the name wasn't well-formed.", ref, table);
    else if (status == ENOMEM)
        error_exit("Insufficient memory to create the semaphore.", ref, table);
}

void handle_sem_error(int status, t_opcode opcode, t_table *table)
{
    char ref[] = "handle_sem_error @ semaphores/error_handler.c";
    if (status == 0)
        return;
    if (opcode == LOCK || opcode == UNLOCK)
    {
        if (status == EINVAL)
            error_exit("Specified semaphore is not valid.", ref, table);
        else if (status == EOVERFLOW)
            error_exit("The maximum allowable value for a semaphore would be exceeded.", ref, table);
        else if (status == EINTR)
            error_exit("The semaphore wait operation was interrupted by a signal.", ref, table);
    }
    else if (opcode == CREATE)
        handle_sem_error_create(status, table);
    else if (opcode == UNLINK)
        handle_sem_error_unlink(status, table);
    else if (opcode == CLOSE)
    {
        if (status == EINVAL)
            error_exit("Specified semaphore is not valid.", ref, table);
    }
}

void safe_sem_handle(sem_t *sem, const char *name, t_opcode opcode, t_table *table)
{
    if (opcode == LOCK)
        handle_sem_error(sem_wait(sem), opcode, table);
    else if (opcode == UNLOCK)
        handle_sem_error(sem_post(sem), opcode, table);
    else if (opcode == UNLINK)
        handle_sem_error(sem_unlink(name), opcode, table);
    else if (opcode == CLOSE)
        handle_sem_error(sem_close(sem), opcode, table);
    else
        error_exit("Unrecognized semaphore operation", "safe_sem_handle @ semaphores/error_handler.c", table);
}
