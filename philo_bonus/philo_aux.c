/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:13:14 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/23 19:13:19 by joaomigu         ###   ########.fr       */
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
 */
void	ft_putstr_fd(const char *s, int fd)
{
	size_t	len;

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
void	error_exit(const char *message, t_table *table)
{
	ft_putstr_fd(R "", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n" RST, STDERR_FILENO);
	if (table)
		clean(table);
	exit(EXIT_FAILURE);
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
