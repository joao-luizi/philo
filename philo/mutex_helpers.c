/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:16:04 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/25 12:16:12 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
