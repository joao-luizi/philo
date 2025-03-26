/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:16:04 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/26 13:38:43 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	safe_get(void *dest, void *src, sem_t *semaphore, t_type type)
{
	if (sem_wait(semaphore) != 0)
		return (ft_putstr_fd("Failed to lock semaphore\n", 2), false);
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
		sem_post(semaphore);
		return (ft_putstr_fd("Unsupported data type\n", 2), false);
	}
	if (sem_post(semaphore) != 0)
		return (ft_putstr_fd("Failed to unlock semaphore\n", 2), false);
	return (true);
}

bool	safe_set(void *dest, void *src, sem_t *semaphore, t_type type)
{
	if (sem_wait(semaphore) != 0)
		return (ft_putstr_fd("Failed to lock semaphore\n", 2), false);
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
		sem_post(semaphore);
		return (ft_putstr_fd("Unsupported data type\n", 2), false);
	}
	if (sem_post(semaphore) != 0)
		return (ft_putstr_fd("Failed to unlock semaphore\n", 2), false);
	return (true);
}

bool	safe_increase(void *dest, sem_t *semaphore, t_type type)
{
	if (sem_wait(semaphore) != 0)
		return (ft_putstr_fd("Failed to lock semaphore\n", 2), false);
	if (type == TYPE_INT)
		*(int *)dest += 1;
	else if (type == TYPE_UINT)
		*(unsigned int *)dest += 1;
	else
	{
		sem_post(semaphore);
		return (ft_putstr_fd("Unsupported data type\n", 2), false);
	}
	if (sem_post(semaphore) != 0)
		return (ft_putstr_fd("Failed to unlock semaphore\n", 2), false);
	return (true);
}
