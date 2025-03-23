/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:06:11 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/23 18:15:37 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Monitors the dinner simulation and checks for philosopher
 *  deaths.
 *
 * This function runs in a separate thread and continuously checks 
 * if any
 * philosophers have died. If a philosopher has died, it sets the 
 end simulation
 * flag and writes the death status to the output.
 *
 * @param data A pointer to the t_table structure containing 
 * the simulation data.
 * @return NULL
 */
void	*monitor_dinner(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->thread_running_count, table->philo_number))
		;
	while (!get_bool(&table->table_mutex, &table->end_simulation))
	{
		i = 0;
		while (i < table->philo_number && !get_bool(&table->table_mutex,
				&table->end_simulation))
		{
			if (philo_died(table->philos + i, table))
			{
				write_status(DEAD, table->philos + i, table);
				set_bool(&table->table_mutex, &table->end_simulation, true);
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

/**
 * @brief Simulates a philosopher's dinner.
 *
 * This function runs in a separate thread for each philosopher and simulates
 * their dinner. It waits for all threads to start, then enters a loop where
 * the philosopher eats, sleeps, and thinks.
 *
 * @param data A pointer to the t_philo structure containing the philosopher's 
 * data.
 * @return NULL
 */
void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	wait_all_threads(table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&table->table_mutex, &table->thread_running_count);
	de_sync_philos(philo, table);
	while (!get_bool(&table->table_mutex, &table->end_simulation))
	{
		if (philo->full)
			break ;
		philo_eat(philo, table);
		write_status(SLEEPING, philo, table);
		usleep(table->time_to_sleep);
		//custom_usleep(table->time_to_sleep, table);
		philo_think(philo, table);
	}
	return (NULL);
}

/**
 * @brief Joins all threads in the simulation.
 *
 * This function joins all philosopher threads and the monitor thread, then 
 * sets
 * the end simulation flag.
 *
 * @param table A pointer to the t_table structure containing the simulation 
 * data.
 * @return true if all threads were joined successfully, false otherwise.
 */
static bool	join_all_threads(t_table *table)
{
	int	i;

	table->start_simulation = get_time(MILLISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_number)
	{
		if (!safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN))
			return (false);
	}
	set_bool(&table->table_mutex, &table->end_simulation, true);
	if (!safe_thread_handle(&table->monitor, NULL, NULL, JOIN))
		return (false);
	return (true);
}

/**
 * @brief Initializes the dinner simulation.
 *
 * This function initializes the simulation by creating threads for each
 * philosopher and the monitor, then starts the simulation.
 *
 * @param table A pointer to the t_table structure containing the simulation 
 * data.
 * @return true if the simulation was initialized successfully, false 
 * otherwise.
 */
bool	dinner_init(t_table *table)
{
	int	i;

	if (table->nbr_limit_meals == 0 || table->philo_number == 0)
		return (true);
	i = -1;
	while (++i < table->philo_number)
	{
		if (table->philo_number < 2)
		{
			if (!safe_thread_handle(&table->philos[0].thread_id, lone_philo,
					&table->philos[0], CREATE))
				return (false);
		}
		else
		{
			if (!safe_thread_handle(&table->philos[i].thread_id,
					dinner_simulation, &table->philos[i], CREATE))
				return (false);
		}
	}
	if (!safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE))
		return (false);
	return (join_all_threads(table));
}
