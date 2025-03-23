/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:10:16 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/23 19:10:31 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define DEBUG false
// default color
# define RST "\033[0m"
// RED Color (Bold)
# define R "\033[1;31m"
// GREEN Color (Bold)
# define G "\033[1;32m"
// YELLOW Color (Bold)
# define Y "\033[1;33m"
// BLUE Color (Bold)
# define B "\033[1;34m"
// MAGENTA Color (Bold)
# define M "\033[1;35m"
// CYAN Color (Bold)
# define C "\033[1;36m"
// WHITE Color (Bold)
# define W "\033[1;37m"

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef enum e_sem_action
{
	SEM_CREATE,
	SEM_INIT,
	CLOSE,
	UNLINK,
	SEM_LOCK,
	SEM_UNLOCK
}	t_sem_action;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DEAD,
}	t_status;
#endif