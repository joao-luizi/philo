/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:18:33 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 11:44:05 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Handles errors related to mutex operations.
 * 
 * This function checks the status of a mutex operation and prints an 
 * appropriate error message if an error occurred. It returns `true` if 
 * the operation was successful and `false` otherwise.
 * 
 * @param status The status code returned by the mutex operation.
 * @param opcode The operation being performed (e.g., LOCK, UNLOCK, 
 * INIT, DESTROY).
 * @return true If the operation was successful, false otherwise.
 */
static bool	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (true);
	else if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		return (printf(R "The value specified by mutex is invalid." RST),
			false);
	else if (status == EINVAL && opcode == INIT)
		return (printf(R "The value specified by attr is invalid." RST), false);
	else if (status == EDEADLK)
		return (printf(R "A deadlock would occur if the thread blocked \
            waiting for mutex." RST), false);
	else if (status == EPERM)
		return (printf(R "The current thread does not hold a lock on \
            mutex." RST), false);
	else if (status == ENOMEM)
		return (printf(R "The process cannot allocate enough memory to \
            create another mutex." RST), false);
	else if (status == EBUSY)
		return (printf(R "Mutex is locked." RST), false);
	else
		return (printf(R "Unknown error\n" RST), false);
}

/**
 * @brief Safely handles mutex operations.
 * 
 * This function performs various mutex operations (e.g., LOCK, UNLOCK, INIT,
 *  DESTROY) 
 * and ensures that errors are handled appropriately. It uses 
 * `handle_mutex_error` to check the status of each operation and print error 
 * messages if necessary.
 * 
 * @param mutex The mutex to operate on.
 * @param opcode The operation to perform (e.g., LOCK, UNLOCK, INIT, DESTROY).
 * @return true If the operation was successful, false otherwise.
 */
bool	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		return (handle_mutex_error(pthread_mutex_lock(mutex), opcode));
	else if (opcode == UNLOCK)
		return (handle_mutex_error(pthread_mutex_unlock(mutex), opcode));
	else if (opcode == INIT)
		return (handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode));
	else if (opcode == DESTROY)
		return (handle_mutex_error(pthread_mutex_destroy(mutex), opcode));
	else
	{
		printf(R "Unrecognized mutex operation\n" RST);
		return (false);
	}
}
