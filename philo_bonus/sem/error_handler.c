
# include "../inc/philo.h"

/**
 * @brief Handles errors related to unlinking a semaphore.
 * 
 * This function checks the status of a semaphore unlink operation and 
 * exits the program with an appropriate error message if an error occurs.
 * 
 * @param status The error code returned by the semaphore unlink operation.
 * @param table The table structure used for resource cleanup.
 */
static void handle_sem_error_unlink(int status, t_table *table)
{
    if (status == EACCES)
        error_exit("The caller does not have permission to unlink this semaphore.", table);
    else if (status == ENAMETOOLONG)
        error_exit("The semaphore name is too long.", table);
    else if (status == ENOENT)
        error_exit("There is no semaphore with the given name.", table);
}

/**
 * @brief Handles errors related to creating a semaphore.
 * 
 * This function checks the status of a semaphore creation operation and 
 * exits the program with an appropriate error message if an error occurs.
 * 
 * @param status The error code returned by the semaphore creation operation.
 * @param table The table structure used for resource cleanup.
 */
static void handle_sem_error_create(int status, t_table *table)
{
    
    if (status == 0)
        return;
    if (status == EACCES)
        error_exit("The semaphore exists, but the caller does not have permission to open it.", table);
    else if (status == EEXIST)
        error_exit("Both O_CREAT and O_EXCL were specified, but a semaphore with this name already exists.", table);
    else if (status == EINVAL)
        error_exit("Invalid semaphore name format or value is greater than SEM_VALUE_MAX.", table);
    else if (status == EMFILE)
        error_exit("The per-process limit on open file descriptors has been reached.", table);
    else if (status == ENAMETOOLONG)
        error_exit("The semaphore name is too long.", table);
    else if (status == ENFILE)
        error_exit("The system-wide limit on total open files has been reached.", table);
    else if (status == ENOENT)
        error_exit("The semaphore does not exist, and O_CREAT was not specified, or the name wasn't well-formed.", table);
    else if (status == ENOMEM)
        error_exit("Insufficient memory to create the semaphore.", table);
}

/**
 * @brief Handles general semaphore errors based on the operation type.
 * 
 * This function checks the status of a semaphore operation (e.g., LOCK, UNLOCK, 
 * CREATE, UNLINK, CLOSE) and calls the appropriate error handler or exits the 
 * program with an error message.
 * 
 * @param status The error code returned by the semaphore operation.
 * @param opcode The semaphore operation being performed (e.g., LOCK, UNLOCK, CREATE).
 * @param table The table structure used for resource cleanup.
 */
static void handle_sem_error(int status, t_sem_action opcode, t_table *table)
{
    if (status == 0)
        return;
    if (opcode == SEM_LOCK || opcode == SEM_UNLOCK)
    {
        if (status == EINVAL)
            error_exit("Specified semaphore is not valid.", table);
        else if (status == EOVERFLOW)
            error_exit("The maximum allowable value for a semaphore would be exceeded.", table);
        else if (status == EINTR)
            error_exit("The semaphore wait operation was interrupted by a signal.", table);
    }
    else if (opcode == SEM_CREATE)
        handle_sem_error_create(status, table);
    else if (opcode == UNLINK)
        handle_sem_error_unlink(status, table);
    else if (opcode == CLOSE)
    {
        if (status == EINVAL)
            error_exit("Specified semaphore is not valid.", table);
    }
}

/**
 * @brief Safely handles semaphore operations.
 * 
 * This function performs various semaphore operations (e.g., LOCK, UNLOCK, CREATE, 
 * UNLINK, CLOSE) and handles errors appropriately. For CREATE, it initializes the 
 * semaphore and updates the pointer.
 * 
 * @param sem A double pointer to the semaphore being operated on.
 * @param name The name of the semaphore (used for CREATE and UNLINK operations).
 * @param opcode The semaphore operation to perform (e.g., LOCK, UNLOCK, CREATE).
 * @param table The table structure used for resource cleanup.
 */
void safe_sem_handle(sem_t **sem, const char *name, t_sem_action opcode, t_table *table)
{
    if (opcode == SEM_LOCK)
        handle_sem_error(sem_wait(*sem), opcode, table);
    else if (opcode == SEM_UNLOCK)
        handle_sem_error(sem_post(*sem), opcode, table);
    else if (opcode == UNLINK)
        handle_sem_error(sem_unlink(name), opcode, table);
    else if (opcode == CLOSE)
        handle_sem_error(sem_close(*sem), opcode, table);
    else if (opcode == SEM_CREATE)
    {
        *sem = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
        if (*sem == SEM_FAILED)
            handle_sem_error(errno, opcode, table);
    }
    else if(opcode == SEM_INIT)
    {
        *sem = sem_open(name, 0);
        if (*sem == SEM_FAILED)
            handle_sem_error(errno, opcode, table);
    }
    else
        error_exit("Unrecognized semaphore operation", table);
}
