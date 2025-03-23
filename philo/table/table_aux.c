/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:06:11 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/23 18:12:25 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Simulates a lone philosopher's dinner.
 *
 * This function runs in a separate thread for a lone philosopher and
 *  simulates
 * their dinner. It waits for all threads to start, then enters a loop
 *  where
 * the philosopher takes a fork and waits for a short period of time.
 *
 * @param data A pointer to the t_philo structure containing the 
 * philosopher's data.
 * @return NULL
 */
void	*lone_philo(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	wait_all_threads(table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&table->table_mutex, &table->thread_running_count);
	write_status(TAKE_FIRST_FORK, philo, table);
	while (!get_bool(&table->table_mutex, &table->end_simulation))
		usleep(30);
	return (NULL);
}

/**
 * @brief De-synchronizes philosophers to prevent simultaneous 
 * actions.
 *
 * This function introduces a delay or thinking period for philosophers
 *  to
 * prevent them from taking actions at the same time.
 *
 * @param philo A pointer to the t_philo structure containing the 
 * philosopher's data.
 * @param table A pointer to the t_table structure containing the 
 * simulation data.
 */
void	de_sync_philos(t_philo *philo, t_table *table)
{
	if (table->philo_number % 2 == 0)
	{
		if (philo->id % 2 == 0)
		{
			usleep(30000);
			//custom_usleep(30000, table);
		}
	}
	else
	{
		if (philo->id % 2 == 0)
			philo_think(philo, table);
	}
}

/**
 * @brief Initializes the table data structure.
 *
 * This function initializes the table data structure by allocating
 *  memory for
 * the philosophers and forks, and initializing the mutexes.
 *
 * @param table A pointer to the t_table structure containing the 
 simulation data.
 * @return true if the table was initialized successfully, false 
 otherwise.
 */
bool	table_init(t_table *table)
{
	int	i;

	table->end_simulation = false;
	table->all_threads_ready = false;
	table->thread_running_count = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_number);
	if (!table->philos)
		return (false);
	if (!safe_mutex_handle(&table->table_mutex, INIT))
		return (false);
	if (!safe_mutex_handle(&table->write_mutex, INIT))
		return (false);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_number);
	if (!table->forks)
		return (false);
	i = 0;
	while (i < table->philo_number)
	{
		if (!safe_mutex_handle(&table->forks[i].fork, INIT))
			return (false);
		table->forks[i].fork_id = i;
		i++;
	}
	return (true);
}
