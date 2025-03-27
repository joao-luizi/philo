/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:58:56 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/27 12:01:51 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

/**
 * @brief Checks if a philosopher has eaten enough meals to be considered full.
 *
 * Retrieves the meal limit and the philosopher's current meal count in a 
 * thread-safe
 * manner. If the limit is reached, it marks the philosopher as full.
 *
 * @param philo Pointer to the philosopher structure.
 * @return true if the philosopher is full or if an error occurred during 
 * safe_get/set;
 *         false otherwise.
 */
static bool	philo_full(t_philo *philo)
{
	int				local_limit_meals;
	unsigned int	local_meal_counter;
	bool			value;

	if (!safe_get(&local_limit_meals, &philo->shared->nbr_limit_meals,
			&philo->shared->table_mutex, TYPE_INT))
		return (ft_putstr_fd("Failed to safely get nbr_limit_meals\n", 2),
			true);
	if (!safe_get(&local_meal_counter, &philo->meal_counter, &philo->philo_mutex,
			TYPE_UINT))
		return (ft_putstr_fd("Failed to safely get meal_counter\n", 2), true);
	if (local_limit_meals > 0 && (int)local_meal_counter == local_limit_meals)
	{
		value = true;
		if (!safe_set(&philo->full, &value, &philo->philo_mutex, TYPE_BOOL))
			return (ft_putstr_fd("Failed to safely set philo full\n", 2), true);
		return (true);
	}
	return (false);
}

/**
 * @brief Checks whether a philosopher has died due to starvation.
 *
 * Locks the philosopher's mutex and checks the time elapsed since the last 
 * meal.
 * If it exceeds `time_to_die`, the philosopher is considered dead.
 *
 * @param philo Pointer to the philosopher structure.
 * @return true if the philosopher died; false if still alive or full, or in 
 * case of an error.
 */
bool	philo_died(t_philo *philo)
{
	unsigned int	elapsed;

	if (pthread_mutex_lock(&philo->philo_mutex) != 0)
		return (ft_putstr_fd("Failed to lock philo mutex\n", 2), false);
	if (philo->full || philo->last_meal_time == 0)
	{
		if (pthread_mutex_unlock(&philo->philo_mutex) != 0)
			return (ft_putstr_fd("Failed to unlock philo mutex\n", 2), false);
		return (false);
	}
	elapsed = get_time(MICROSECOND) - philo->last_meal_time;
	if (elapsed >= philo->shared->time_to_die)
	{
		if (pthread_mutex_unlock(&philo->philo_mutex) != 0)
			return (ft_putstr_fd("Failed to unlock philo mutex\n", 2), true);
		return (true);
	}
	if (pthread_mutex_unlock(&philo->philo_mutex) != 0)
		return (ft_putstr_fd("Failed to unlock philo mutex\n", 2), false);
	return (false);
}

/**
 * @brief Handles the thinking phase of a philosopher.
 *
 * Logs the THINKING state and applies a small sleep delay for odd-numbered 
 * philosopher
 * counts to help stagger the execution and avoid contention for forks.
 *
 * @param philo Pointer to the philosopher structure.
 */
void	philo_think(t_philo *philo)
{
	unsigned int	local_philo_number;
	unsigned int	local_time_to_think;

	write_states(THINKING, philo);
	if (!safe_get(&local_philo_number, &philo->shared->philo_number,
			&philo->shared->table_mutex, TYPE_UINT))
	{
		ft_putstr_fd("Failed to safely get philo_number\n", 2);
		return ;
	}
	if (!safe_get(&local_time_to_think, &philo->shared->time_to_think,
			&philo->shared->table_mutex, TYPE_UINT))
	{
		ft_putstr_fd("Failed to safely get time_to_think\n", 2);
		return ;
	}
	if (local_philo_number % 2 == 0)
		return ;
	custom_sleep((local_time_to_think) * 0.5, philo->shared);
}

/**
 * @brief Locks both forks for a philosopher in the correct order.
 *
 * First locks the mutex for the first fork and logs the action. Then does
 *  the same for
 * the second fork. If locking or logging fails at any point, the function
 *  returns false.
 *
 * @param philo Pointer to the philosopher structure.
 * @return true if both forks were successfully taken; false otherwise.
 */
static bool	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->first_fork->fork) != 0)
		return (ft_putstr_fd("Failed to lock fork mutex\n", 2), false);
	if (!write_states(TAKE_FIRST_FORK, philo))
		return (false);
	if (pthread_mutex_lock(&philo->second_fork->fork) != 0)
		return (ft_putstr_fd("Failed to lock fork mutex\n", 2), false);
	if (!write_states(TAKE_SECOND_FORK, philo))
		return (false);
	return (true);
}

/**
 * @brief Executes the eating routine for a philosopher.
 *
 * The philosopher locks both forks, logs the EATING state, updates the last
 *  meal time,
 * increments the meal counter, and sleeps for the eating duration. If the 
 * philosopher
 * has reached the meal limit, they are marked as full. Finally, the forks 
 * are released.
 *
 * @param philo Pointer to the philosopher structure.
 * @param shared Pointer to the shared simulation data.
 * @return true if the eating routine completed successfully; false otherwise.
 */
bool	philo_eat(t_philo *philo, t_shared *shared)
{
	size_t	current_time;

	take_forks(philo);
	current_time = get_time(MICROSECOND);
	if (!write_states(EATING, philo))
		return (false);
	if (!safe_set(&philo->last_meal_time, &current_time, &philo->philo_mutex,
			TYPE_SIZE_T))
		return (ft_putstr_fd("Failed to set last_meal_time\n", 2), false);
	custom_sleep(shared->time_to_eat, shared);
	if (!safe_increase(&philo->meal_counter, &philo->philo_mutex, TYPE_UINT))
		return (ft_putstr_fd("Failed to increase meal_counter\n", 2), false);
	if (philo_full(philo))
	{
		if (!safe_set(&philo->full, &(bool){true}, &philo->philo_mutex,
			TYPE_BOOL))
			return (ft_putstr_fd("Failed to set philo full\n", 2), false);
	}
	if (pthread_mutex_unlock(&philo->first_fork->fork) != 0)
		return (ft_putstr_fd("Failed to unlock fork mutex\n", 2), false);
	if (pthread_mutex_unlock(&philo->second_fork->fork) != 0)
		return (ft_putstr_fd("Failed to unlock fork mutex\n", 2), false);
	return (true);
}
