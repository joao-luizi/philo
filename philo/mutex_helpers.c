/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:16:04 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/26 14:57:37 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**

    @brief Safely retrieves a value from a source location while holding a mutex lock.
    This function locks the provided mutex, copies the value from the source location
    to the destination location, and then unlocks the mutex. If the mutex lock or
    unlock operations fail, an error message is printed and the function returns false.
    @param dest The destination location to store the retrieved value.
    @param src The source location to retrieve the value from.
    @param mutex The mutex to lock while accessing the source location.
    @param type The type of data being retrieved (e.g. TYPE_BOOL, TYPE_INT, etc.).
    @return true if the operation is successful, false otherwise.
 */
bool	safe_get(void *dest, void *src, pthread_mutex_t *mutex, t_type type)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (ft_putstr_fd("Failed to lock mutex\n", 2), false);
	if (type == TYPE_BOOL)
		*(bool *)dest = *(bool *)src;
	else if (type == TYPE_INT)
		*(int *)dest = *(int *)src;
	else if (type == TYPE_LONG)
		*(long *)dest = *(long *)src;
	else if (type == TYPE_UINT)
		*(unsigned int *)dest = *(unsigned int *)src;
	else if (type == TYPE_SIZE_T)
		*(size_t *)dest = *(size_t *)src;
	else
	{
		pthread_mutex_unlock(mutex);
		return (ft_putstr_fd("Unsupported data type\n", 2), false);
	}
	if (pthread_mutex_unlock(mutex) != 0)
		return (ft_putstr_fd("Failed to unlock mutex\n", 2), false);
	return (true);
}
/**

    @brief Safely sets a value at a destination location while holding a mutex lock.
    This function locks the provided mutex, copies the value from the source location
    to the destination location, and then unlocks the mutex. If the mutex lock or
    unlock operations fail, an error message is printed and the function returns false.
    @param dest The destination location to set the value at.
    @param src The source location to retrieve the value from.
    @param mutex The mutex to lock while accessing the destination location.
    @param type The type of data being set (e.g. TYPE_BOOL, TYPE_INT, etc.).
    @return true if the operation is successful, false otherwise.
*/
bool	safe_set(void *dest, void *src, pthread_mutex_t *mutex, t_type type)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (ft_putstr_fd("Failed to lock mutex\n", 2), false);
	if (type == TYPE_BOOL)
		*(bool *)dest = *(bool *)src;
	else if (type == TYPE_INT)
		*(int *)dest = *(int *)src;
	else if (type == TYPE_LONG)
		*(long *)dest = *(long *)src;
	else if (type == TYPE_UINT)
		*(unsigned int *)dest = *(unsigned int *)src;
	else if (type == TYPE_SIZE_T)
		*(size_t *)dest = *(size_t *)src;
	else
	{
		pthread_mutex_unlock(mutex);
		return (ft_putstr_fd("Unsupported data type\n", 2), false);
	}
	if (pthread_mutex_unlock(mutex) != 0)
		return (ft_putstr_fd("Failed to unlock mutex\n", 2), false);
	return (true);
}

/**
    @brief Safely increments a value at a destination location while holding a mutex lock.
    This function locks the provided mutex, increments the value at the destination
    location, and then unlocks the mutex. If the mutex lock or unlock operations fail,
    an error message is printed and the function returns false. Only integer types
    (TYPE_INT and TYPE_UINT) are supported for increment operations.
    @param dest The destination location to increment the value at.
    @param mutex The mutex to lock while accessing the destination location.
    @param type The type of data being incremented (e.g. TYPE_INT, TYPE_UINT).
    @return true if the operation is successful, false otherwise.
*/
bool	safe_increase(void *dest, pthread_mutex_t *mutex, t_type type)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (ft_putstr_fd("Failed to lock mutex\n", 2), false);
	if (type == TYPE_INT)
		*(int *)dest += 1;
	else if (type == TYPE_UINT)
		*(unsigned int *)dest += 1;
	else
	{
		pthread_mutex_unlock(mutex);
		return (ft_putstr_fd("Unsupported data type\n", 2), false);
	}
	if (pthread_mutex_unlock(mutex) != 0)
		return (ft_putstr_fd("Failed to unlock mutex\n", 2), false);
	return (true);
}
