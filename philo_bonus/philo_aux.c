# include "inc/philo.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:03:50 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 11:16:27 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

/**
 * @brief Writes a string to the specified file descriptor.
 * 
 * This function calculates the length of the string and writes it 
 * to the given file descriptor using the `write` system call.
 * 
 * @param s The string to write.
 * @param fd The file descriptor to write to.
 *           - 0: Standard input
 *           - 1: Standard output
 *           - 2: Standard error
 */
void	ft_putstr_fd(const char *s, int fd)
{
    size_t len;

    len = 0;
    while (s[len])
        len++;
    write(fd, s, len);
}

/**
 * @brief Exits the program gracefully after handling a critical error.
 * 
 * This function prints an error message, cleans up resources, and exits
 * the program with a failure status.
 * 
 * @param message The error message to display.
 * @param table The table structure containing resources to clean up.
 */
void error_exit(const char *message, t_table *table)
{
    // Print the error message to stderr
    ft_putstr_fd(R "", STDERR_FILENO);
    ft_putstr_fd(message, STDERR_FILENO);
    ft_putstr_fd("\n" RST, STDERR_FILENO);
    if (table)
        clean(table);
    exit(EXIT_FAILURE);
}

/**
 * @brief Custom implementation of usleep that takes into 
 * account the end of simulation flag.
 * 
 * This function pauses the execution of the current thread 
 * for a specified amount of time.
 * It checks the end of simulation flag and breaks the loop 
 * if it's set.
 * 
 * @param usec The time to sleep in microseconds.
 * @param table A pointer to the table containing the end of 
 * simulation flag.
 */
void	custom_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECOND);
	while (1)
	{
		elapsed = get_time(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining <= 0
            || get_bool(table->table_semaphore, table, &table->end_simulation))
			break ;
		if (remaining < 500)
		{
			while (get_time(MICROSECOND) - start < usec)
				;
		}
		else
		{
			if (remaining * 0.8 < 1000)
				usleep(1000);
			else
				usleep(remaining * 0.8);
		}
	}
}

/**
 * @brief Retrieves the current time in the specified time unit.
 * 
 * This function uses the gettimeofday function to get the current
 *  time and converts it to the desired time unit.
 * 
 * @param timecode The time unit to retrieve the time in. Can be 
 * SECOND, MILLISECOND, or MICROSECOND.
 * @return The current time in the specified time unit.
 */
long	get_time(t_time_code timecode)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (timecode == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (timecode == MILLISECOND)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (timecode == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (0);
}

