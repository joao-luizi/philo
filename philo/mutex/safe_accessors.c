/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_accessors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:18:12 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 11:42:09 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Safely retrieves the value of a boolean variable.
 * 
 * This function locks the provided mutex, retrieves the value of the boolean 
 * variable, and then unlocks the mutex.
 * 
 * @param mutex The mutex protecting the boolean variable.
 * @param dest Pointer to the boolean variable to retrieve.
 * @return The value of the boolean variable.
 */
bool	get_bool(t_mtx *mutex, bool *dest)
{
	bool	result;

	safe_mutex_handle(mutex, LOCK);
	result = *dest;
	safe_mutex_handle(mutex, UNLOCK);
	return (result);
}

/**
 * @brief Safely sets the value of a boolean variable.
 * 
 * This function locks the provided mutex, sets the value of the boolean 
 * variable, and then unlocks the mutex.
 * 
 * @param mutex The mutex protecting the boolean variable.
 * @param dest Pointer to the boolean variable to set.
 * @param value The value to set the boolean variable to.
 */
void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/**
 * @brief Safely retrieves the value of a long variable.
 * 
 * This function locks the provided mutex, retrieves the value of the long 
 * variable, and then unlocks the mutex.
 * 
 * @param mutex The mutex protecting the long variable.
 * @param dest Pointer to the long variable to retrieve.
 * @return The value of the long variable.
 */
long	get_long(t_mtx *mutex, long *dest)
{
	long	result;

	safe_mutex_handle(mutex, LOCK);
	result = *dest;
	safe_mutex_handle(mutex, UNLOCK);
	return (result);
}

/**
 * @brief Safely sets the value of a long variable.
 * 
 * This function locks the provided mutex, sets the value of the long 
 * variable, and then unlocks the mutex.
 * 
 * @param mutex The mutex protecting the long variable.
 * @param dest Pointer to the long variable to set.
 * @param value The value to set the long variable to.
 */
void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

/**
 * @brief Safely increments the value of a long variable.
 * 
 * This function locks the provided mutex, increments the value of the long 
 * variable, and then unlocks the mutex.
 * 
 * @param mutex The mutex protecting the long variable.
 * @param dest Pointer to the long variable to increment.
 */
void	increase_long(t_mtx *mutex, long *dest)
{
	safe_mutex_handle(mutex, LOCK);
	(*dest)++;
	safe_mutex_handle(mutex, UNLOCK);
}
