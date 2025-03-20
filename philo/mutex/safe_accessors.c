/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_accessors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:18:12 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 00:18:14 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	get_bool(t_mtx *mutex, bool *dest)
{
	bool	result;

	safe_mutex_handle(mutex, LOCK);
	result = *dest;
	safe_mutex_handle(mutex, UNLOCK);
	return (result);
}

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *dest)
{
	long	result;

	safe_mutex_handle(mutex, LOCK);
	result = *dest;
	safe_mutex_handle(mutex, UNLOCK);
	return (result);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

void	increase_long(t_mtx *mutex, long *dest)
{
	safe_mutex_handle(mutex, LOCK);
	(*dest)++;
	safe_mutex_handle(mutex, UNLOCK);
}
