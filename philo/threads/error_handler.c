/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:04:12 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 11:15:27 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Handles thread creation errors.
 *
 * This function handles errors that may occur during thread creation, such as
 * lack of resources or invalid thread attributes.
 *
 * @param status The status code returned by the thread operation.
 * @param opcode The operation code (CREATE, JOIN, or DETACH).
 * @return True if the error is handled successfully, false otherwise.
 */
static bool	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (true);
	else if (status == EAGAIN)
		return (printf(R "No resources to create another thread." RST), false);
	else if (status == EPERM)
		return (printf(R "The caller does not have appropriate \
            permissions" RST), false);
	else if (status == EINVAL && opcode == CREATE)
		return (printf(R "The value specified by attr is invalid." RST), false);
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		return (printf(R "The value specified by thread is not joinable" RST),
			false);
	else if (status == ESRCH)
		return (printf(R "No thread could be found corresponding to that specified by the given thread ID,\
				thread" RST), false);
	else if (status == EDEADLK)
		return (printf(R "A deadlock was detected or the value of thread specifies the \
            calling thread" RST), false);
	else
		return (printf(R "Unrecognized thread operation\n" RST), false);
}

/**
 * @brief Handles thread operations safely.
 *
 * This function handles thread creation, joining, and detachment safely by
 * checking the operation code and handling any errors that may occur.
 *
 * @param thread The thread to operate on.
 * @param foo The function to be executed by the thread.
 * @param data The data to be passed to the thread function.
 * @param opcode The operation code (CREATE, JOIN, or DETACH).
 * @return True if the operation is successful, false otherwise.
 */
bool	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode opcode)
{
	if (opcode == CREATE)
		return (handle_thread_error(pthread_create(thread, NULL, foo, data),
				opcode));
	else if (opcode == JOIN)
		return (handle_thread_error(pthread_join(*thread, NULL), opcode));
	else if (opcode == DETACH)
		return (handle_thread_error(pthread_detach(*thread), opcode));
	else
		return (printf(R "Unrecognized thread operation\n" RST), false);
}
