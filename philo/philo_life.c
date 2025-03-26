/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:31 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/26 23:27:01 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/message.h"
#include "inc/philo.h"

/**
 * @brief Writes the philosopher's current state to the console in a thread-safe manner.
 *
 * This function locks the shared write mutex before printing the philosopher's state.
 * It first checks if the simulation has ended and returns early if so. If the simulation
 * is still running, it prints a message corresponding to the provided status.
 *
 * @param status The current status of the philosopher (e.g., eating, sleeping).
 * @param philo Pointer to the philosopher whose state is being printed.
 * 
 * @return true if the message was written successfully or if simulation ended; 
 *         false if a mutex lock/unlock or state retrieval fails.
 *
 * @see safe_get
 */
bool	write_states(t_status status, t_philo *philo)
{
	unsigned int	elapsed;
	bool			local_end_simulation;

	if (pthread_mutex_lock(philo->shared->table_mutex) != 0)
		return (ft_putstr_fd("Failed to lock write mutex\n", 2), false);
	//if (!safe_get(&local_end_simulation, &philo->shared->end_simulation,
	//	philo->shared->table_mutex, TYPE_BOOL))
	//	return (ft_putstr_fd("Failed to get end_simulation\n", 2), false);
	elapsed = get_time(MILLISECOND) - philo->shared->start_simulation;
	local_end_simulation = philo->shared->end_simulation;
	if (local_end_simulation)
		return (pthread_mutex_unlock(philo->shared->table_mutex), true);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
		printf("%-6u %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING)
		printf("%-6u %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING)
		printf("%-6u %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING)
		printf("%-6u %d is thinking\n", elapsed, philo->id);
	else if (status == DEAD)
		printf("%-6u %d is dead\n", elapsed, philo->id);
	if (pthread_mutex_unlock(philo->shared->table_mutex) != 0)
		return (ft_putstr_fd("Failed to unlock write mutex\n", 2), false);
	return (true);
}

/**
 * @brief Desynchronizes philosophers to prevent simultaneous resource access at simulation start.
 *
 * For even-numbered philosopher counts:
 * - Even-indexed philosophers sleep briefly to create offset.
 * For odd-numbered counts:
 * - Even-indexed philosophers begin by thinking.
 *
 * This helps reduce contention for forks in the initial phase of the simulation.
 *
 * @param philo Pointer to the philosopher to be desynchronized.
 * @note This function is static and intended for internal use only.
 * @see safe_get
 */
static void	de_sync_philos(t_philo *philo)
{
	t_shared		*shared;
	unsigned int	local_philo_number;
	unsigned int	local_philo_id;

	shared = philo->shared;
	if (!safe_get(&local_philo_number, &shared->philo_number,
			shared->table_mutex, TYPE_UINT))
		return (ft_putstr_fd("Failed to safely get philo_number\n", 2),
			(void)0);
	if (!safe_get(&local_philo_id, &philo->id, philo->philo_mutex, TYPE_UINT))
		return (ft_putstr_fd("Failed to safely get philo_number\n", 2),
			(void)0);
	if (local_philo_number % 2 == 0)
	{
		if (local_philo_id % 2 == 0)
			usleep(30000);
	}
	else
	{
		if (local_philo_id % 2 == 0)
			philo_think(philo);
	}
}

/**
 * @brief Entry point for a single philosopher thread when only one philosopher exists.
 *
 * Handles the special case of a simulation with just one philosopher. It initializes
 * `last_meal_time`, attempts to take a fork, and waits for the simulation to end.
 *
 * @param args Pointer to a `t_philo` struct representing the philosopher.
 * @return NULL Always returns NULL; designed for pthread usage.
 * @note The philosopher takes the first fork and waits for `end_simulation` to become true.
 * @see safe_get, safe_set, write_states
 */
void	*philo_life_single(void *args)
{
	t_philo	*philo;
	bool	local_end_simulation;
	size_t	current_time;

	philo = (t_philo *)args;
	if (!safe_get(&local_end_simulation, &philo->shared->end_simulation,
			philo->shared->table_mutex, TYPE_BOOL))
		return (ft_putstr_fd("Failed to safely get end_simulation\n", 2), NULL);
	current_time = get_time(MILLISECOND);
	if (!safe_set(&philo->last_meal_time, &current_time, philo->philo_mutex,
			TYPE_SIZE_T))
		return (ft_putstr_fd("Failed to safely set last_meal_time\n", 2), NULL);
	if (!write_states(TAKE_FIRST_FORK, philo))
		return (NULL);
	while (!local_end_simulation)
	{
		if (!safe_get(&local_end_simulation, &philo->shared->end_simulation,
				philo->shared->table_mutex, TYPE_BOOL))
			return (ft_putstr_fd("Failed to safely get end_simulation\n", 2),
				NULL);
		usleep(30);
	}
	return (NULL);
}

/**
 * @brief Sets up initial philosopher data before starting the main life loop.
 *
 * Retrieves the current simulation time and stores it as the philosopher's last meal time.
 * Also checks if the simulation has already ended.
 *
 * @param philo Pointer to the philosopher to initialize.
 * @param local_end_simulation Pointer to a boolean that will store the current simulation state.
 * 
 * @return true on successful setup; false if `safe_get` or `safe_set` fails.
 *
 * @see safe_get, safe_set
 */
static bool	philo_setup(t_philo *philo, bool *local_end_simulation)
{
	size_t	current_time;

	if (!safe_get(local_end_simulation, &philo->shared->end_simulation,
			philo->shared->table_mutex, TYPE_BOOL))
		return (ft_putstr_fd("Failed to safely get end_simulation\n", 2),
			false);
	current_time = get_time(MILLISECOND);
	if (!safe_set(&philo->last_meal_time, &current_time, philo->philo_mutex,
			TYPE_SIZE_T))
		return (ft_putstr_fd("Failed to safely set last_meal_time\n", 2),
			false);
	return (true);
}

/**
 * @brief Entry point for each philosopher thread in the multi-philosopher simulation.
 *
 * Sets up initial state, desynchronizes execution to reduce contention, and enters
 * the main philosopher routine of eating, sleeping, and thinking.
 *
 * The loop continues until the shared `end_simulation` flag is set or the philosopher
 * becomes full (if a meal count limit is used).
 *
 * @param args Pointer to a `t_philo` struct representing the philosopher.
 * @return NULL Always returns NULL; designed for pthread usage.
 * @see philo_setup, de_sync_philos, safe_get, philo_eat, write_states, custom_sleep, philo_think
 */
void	*philo_life_many(void *args)
{
	t_philo	*philo;
	bool	local_end_simulation;
	bool	philo_full;

	philo = (t_philo *)args;
	if (!philo_setup(philo, &local_end_simulation))
		return (NULL);
	de_sync_philos(philo);
	while (!local_end_simulation)
	{
		if (!safe_get(&local_end_simulation, &philo->shared->end_simulation,
				philo->shared->table_mutex, TYPE_BOOL))
			return (ft_putstr_fd("Failed to get end_simulation\n", 2), NULL);
		philo_eat(philo, philo->shared);
		if (!safe_get(&philo_full, &philo->full, philo->philo_mutex, TYPE_BOOL))
			return (ft_putstr_fd("Failed to get philo_full\n", 2), NULL);
		write_states(SLEEPING, philo);
		custom_sleep(philo->shared->time_to_sleep / 1000, philo->shared);
		philo_think(philo);
		if (philo_full)
			return (NULL);
	}
	return (NULL);
}
