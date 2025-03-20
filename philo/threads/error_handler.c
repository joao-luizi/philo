/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:04:12 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 00:06:00 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
