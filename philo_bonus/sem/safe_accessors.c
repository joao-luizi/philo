/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_accessors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:18:12 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 13:36:22 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Safely retrieves the value of a boolean variable using a semaphore.
 * 
 * This function locks the provided semaphore, retrieves the value of the boolean 
 * variable, and then unlocks the semaphore.
 * 
 * @param sem The semaphore protecting the boolean variable.
 * @param table The table structure used for error handling and cleanup.
 * @param dest Pointer to the boolean variable to retrieve.
 * @return The value of the boolean variable.
 */
bool	get_bool(sem_t *sem, t_table *table, bool *dest)
{
	bool	result;

	safe_sem_handle(&sem, NULL, SEM_LOCK, table);
	result = *dest;
	safe_sem_handle(&sem, NULL, SEM_UNLOCK, table);
	return (result);
}

/**
 * @brief Safely sets the value of a boolean variable using a semaphore.
 * 
 * This function locks the provided semaphore, sets the value of the boolean 
 * variable, and then unlocks the semaphore.
 * 
 * @param sem The semaphore protecting the boolean variable.
 * @param table The table structure used for error handling and cleanup.
 * @param dest Pointer to the boolean variable to set.
 * @param value The value to set the boolean variable to.
 */
void	set_bool(sem_t *sem, t_table *table, bool *dest, bool value)
{
	safe_sem_handle(&sem, NULL, SEM_LOCK, table);
	*dest = value;
	safe_sem_handle(&sem, NULL, SEM_UNLOCK, table);
}

/**
 * @brief Safely retrieves the value of a long variable using a semaphore.
 * 
 * This function locks the provided semaphore, retrieves the value of the long 
 * variable, and then unlocks the semaphore.
 * 
 * @param sem The semaphore protecting the long variable.
 * @param table The table structure used for error handling and cleanup.
 * @param dest Pointer to the long variable to retrieve.
 * @return The value of the long variable.
 */
long	get_long(sem_t *sem, t_table *table, long *dest)
{
	long	result;

	safe_sem_handle(&sem, NULL, SEM_LOCK, table);
	result = *dest;
	safe_sem_handle(&sem, NULL, SEM_UNLOCK, table);
	return (result);
}

/**
 * @brief Safely sets the value of a long variable using a semaphore.
 * 
 * This function locks the provided semaphore, sets the value of the long 
 * variable, and then unlocks the semaphore.
 * 
 * @param sem The semaphore protecting the long variable.
 * @param table The table structure used for error handling and cleanup.
 * @param dest Pointer to the long variable to set.
 * @param value The value to set the long variable to.
 */
void	set_long(sem_t *sem, t_table *table, long *dest, long value)
{
	safe_sem_handle(&sem, NULL, SEM_LOCK, table);
	*dest = value;
	safe_sem_handle(&sem, NULL, SEM_UNLOCK, table);
}

/**
 * @brief Safely increments the value of a long variable using a semaphore.
 * 
 * This function locks the provided semaphore, increments the value of the long 
 * variable, and then unlocks the semaphore.
 * 
 * @param sem The semaphore protecting the long variable.
 * @param table The table structure used for error handling and cleanup.
 * @param dest Pointer to the long variable to increment.
 */
void	increase_long(sem_t *sem, t_table *table, long *dest)
{
	safe_sem_handle(&sem, NULL, SEM_LOCK, table);
	(*dest)++;
	safe_sem_handle(&sem, NULL, SEM_UNLOCK, table);
}
