/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:03:50 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/28 13:02:06 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

/**
 * @brief Sleeps for a given amount of time, checking periodically if the
 * simulation should end.
 *
 * This function performs a sleep for the specified number of milliseconds
 * (`sleep_time_ms`),
 * but instead of sleeping all at once, it does so in small intervals (100 ms
 *  by default).
 * Between each interval, it checks the shared `end_simulation` flag to allow
 *  an early exit
 * if the simulation is requested to stop. This allows for a more responsive
 * simulation shutdown.
 *
 * @param sleep_time_ms The total amount of time to sleep, in milliseconds.
 * @param shared Pointer to a shared data structure that includes the
 * `end_simulation` flag
 *               and the mutex protecting access to it.
 *
 * @note If `safe_get` fails to retrieve the `end_simulation` value, an error
 * message is printed
 *       and the function returns early.
 *
 * @see safe_get
 */
void	custom_sleep(unsigned int sleep_time_ms, t_shared *shared)
{
	unsigned int	start_time;
	unsigned int	current_time;
	unsigned int	elapsed_time;
	bool			end_simulation;

	end_simulation = false;
	start_time = get_time(MICROSECOND);
	if (sleep_time_ms <= 100)
		return ;
	usleep(sleep_time_ms - 100);
	while (!end_simulation)
	{
		if (!safe_get(&end_simulation, &shared->end_simulation,
				&shared->table_mutex, TYPE_BOOL))
		{
			ft_putstr_fd("Failed to safely get end_simulation\n", 2);
			return ;
		}
		current_time = get_time(MICROSECOND);
		elapsed_time = current_time - start_time;
		if (elapsed_time >= sleep_time_ms)
			break ;
		usleep(100);
	}
}

/**
 * @brief Allocates memory safely.
 *
 * This function allocates memory using malloc, checks for
 * allocation errors,
 * and initializes the allocated memory to zero.
 *
 * @param bytes The number of bytes to allocate.
 * @return A pointer to the allocated memory, or NULL if
 * allocation failed.
 */
void	*ft_calloc(size_t bytes)
{
	void	*ret;

	if (bytes == 0)
		return (NULL);
	ret = malloc(bytes);
	if (!ret)
	{
		printf(R "Error on memory allocation\n" RST);
		return (NULL);
	}
	memset(ret, 0, bytes);
	return (ret);
}

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
 * @brief Retrieves the current time in the specified time unit.
 *
 * This function uses the gettimeofday function to get the current
 *  time and converts it to the desired time unit.
 *
 * @param timecode The time unit to retrieve the time in. Can be
 * SECOND, MILLISECOND, or MICROSECOND.
 * @return The current time in the specified time unit.
 */
unsigned int	get_time(t_time_code timecode)
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
