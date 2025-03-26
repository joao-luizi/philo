/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:19:40 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/25 18:31:20 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
#include <semaphore.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <signal.h>


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
	DEAD
}	t_status;

typedef enum e_type
{
	TYPE_BOOL,
	TYPE_INT,
	TYPE_LONG,
	TYPE_UINT,
	TYPE_SIZE_T
}	t_type;

#endif