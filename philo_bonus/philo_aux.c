/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:03:50 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/25 13:42:17 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"



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
