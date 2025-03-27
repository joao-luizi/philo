/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:17 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/27 00:14:06 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/message.h"
#include "inc/philo.h"

/**
 * @brief Checks if a philosopher has died and updates the simulation state accordingly.
 *
 * This function verifies if the philosopher at the given index has died. If so,
 * it writes the DEAD state, sets the `end_simulation` flag in the shared structure
 * (thread-safely), and returns true. If no death is detected, it returns false.
 *
 * @param table Pointer to the table structure containing philosophers and shared data.
 * @param i Index of the philosopher to check.
 * @return true if a philosopher died and simulation was updated; false otherwise.
 */
static bool	check_philo_died(t_table *table, unsigned int i)
{
	bool	set_value;

	if (philo_died(table->philos + i))
	{
		if (!write_states(DEAD, table->philos + i))
			return (false);
		set_value = true;
		if (!safe_set(&table->shared->end_simulation, &set_value,
				table->shared->table_mutex, TYPE_BOOL))
			return (ft_putstr_fd("Failed to safely set end_simulation\n", 2),
				false);
		return (true);
	}
	return (false);
}

/**
 * @brief Monitors the status of all philosophers to detect any that may have died.
 *
 * This function iterates through all philosophers, checking if any have died or if
 * the simulation has already ended. It uses thread-safe getters to read the 
 * `end_simulation` flag and calls `check_philo_died()` on each philosopher.
 *
 * @param table Pointer to the table structure.
 * @param local_end_simulation Pointer to a local copy of the simulation end flag.
 * @return true if monitoring should stop (due to death or end flag); false otherwise.
 */
static bool	monitor_philosophers(t_table *table, bool *local_end_simulation)
{
	unsigned int	i;

	i = 0;
	while (i < table->shared->philo_number && !(*local_end_simulation))
	{
		if (!safe_get(local_end_simulation, &table->shared->end_simulation,
				table->shared->table_mutex, TYPE_BOOL))
			return (ft_putstr_fd("Failed to safely get end_simulation\n", 2),
				false);
		if (*local_end_simulation || check_philo_died(table, i))
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Thread routine that monitors all philosophers throughout the simulation.
 *
 * This function runs as a separate monitoring thread. It periodically checks whether
 * any philosopher has died or if the simulation has ended, using `monitor_philosophers()`.
 * It sleeps briefly between checks to reduce CPU usage.
 *
 * @param args Pointer to the table structure passed to the thread.
 * @return NULL when monitoring ends, either due to a philosopher's death or simulation end.
 */
void	*monitor(void *args)
{
	t_table	*table;
	bool	local_end_simulation;

	table = (t_table *)args;
	if (!safe_get(&local_end_simulation, &table->shared->end_simulation,
			table->shared->table_mutex, TYPE_BOOL))
		return (ft_putstr_fd("Failed to safely get end_simulation\n", 2), NULL);
	while (!local_end_simulation)
	{
		if (monitor_philosophers(table, &local_end_simulation))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
