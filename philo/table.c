/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:49:10 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/27 00:30:57 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/message.h"
#include "inc/philo.h"

/**
 * @brief Assigns forks to a philosopher.
 *
 * Depending on the philosopher's ID (even or odd), the order in which the forks
 * are picked up changes to prevent deadlock.
 *
 * @param philo Pointer to the philosopher to assign forks to.
 * @param forks Array of forks on the table.
 * @param philo_pos Position of the philosopher in the array.
 * @param philo_number Total number of philosophers at the table.
 */
static void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos,
		unsigned int philo_number)
{
	philo->first_fork = &forks[(philo_pos + 1) % philo_number];
	philo->second_fork = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_number];
	}
}

/**
 * @brief Initializes all philosopher structures in the table.
 *
 * Allocates memory for each philosopher, initializes their data fields,
 * assigns forks, and sets up their mutex and thread data.
 *
 * @param table Pointer to the main table structure.
 * @return true if initialization is successful, false otherwise.
 */
static bool	philos_init(t_table *table)
{
	unsigned int	i;

	table->philos = ft_calloc(sizeof(t_philo) * table->shared->philo_number);
	if (!table->philos)
		return (printf("Failed to allocate memory for philosophers\n"), false);
	i = 0;
	while (i < table->shared->philo_number)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meal_counter = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].full = false;
		table->philos[i].shared = table->shared;
		assign_forks(&table->philos[i], table->forks, i,
			table->shared->philo_number);
		table->philos[i].philo_mutex = ft_calloc(sizeof(pthread_mutex_t));
		if (!table->philos[i].philo_mutex
			|| pthread_mutex_init(table->philos[i].philo_mutex, NULL) != 0)
			return (printf("Failed to init philo mutex %u\n", i), false);
		table->philos[i].thread_id = ft_calloc(sizeof(pthread_t));
		if (!table->philos[i].thread_id)
			return (printf("Failed to alloc mem for id %u\n", i), false);
		i++;
	}
	return (true);
}

/**
 * @brief Initializes the dining table with forks and philosophers.
 *
 * Allocates memory for all required structures and initializes mutexes
 * associated with forks. Also starts philosopher initialization.
 *
 * @param table Pointer to the table structure to initialize.
 * @return true if successful, false otherwise.
 */
bool	table_init(t_table *table)
{
	unsigned int	i;

	table->forks = NULL;
	table->philos = NULL;
	table->monitor = ft_calloc(sizeof(pthread_t));
	if (!table->monitor)
		return (printf("Failed to allocate memory for monitor thread\n"),
			false);
	table->forks = ft_calloc(sizeof(t_fork) * table->shared->philo_number);
	if (!table->forks)
		return (printf("Failed to allocate memory for forks\n"), false);
	i = 0;
	while (i < table->shared->philo_number)
	{
		table->forks[i].fork = ft_calloc(sizeof(pthread_mutex_t));
		if (!table->forks[i].fork || pthread_mutex_init(table->forks[i].fork,
				NULL) != 0)
			return (printf("Failed to initialize fork mutex %u\n", i), false);
		table->forks[i].fork_id = i;
		i++;
	}
	return (!philos_init(table));
}

/**
 * @brief Creates philosopher threads and the monitor thread.
 *
 * Depending on the number of philosophers, it launches the appropriate routine
 * (`philo_life_single` or `philo_life_many`) for each thread. Also creates
 * the monitoring thread and starts the simulation timer.
 *
 * @param table Pointer to the table containing philosophers and shared data.
 * @return true if all threads are created successfully, false otherwise.
 */
static bool	create_threads(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->shared->philo_number)
	{
		if (table->shared->philo_number == 1)
		{
			if (pthread_create(table->philos[i].thread_id, NULL,
					philo_life_single, &table->philos[i]) != 0)
				return (ft_putstr_fd("failed to create thread\n", 2), false);
		}
		else
		{
			if (pthread_create(table->philos[i].thread_id, NULL,
					philo_life_many, &table->philos[i]) != 0)
				return (ft_putstr_fd("failed to create thread\n", 2), false);
		}
		i++;
	}
	if (pthread_create(table->monitor, NULL, monitor, table) != 0)
		return (ft_putstr_fd("Failed to create monitor thread\n", 2), false);
	table->shared->start_simulation = get_time(MICROSECOND);
	if (pthread_mutex_unlock(table->shared->table_mutex) != 0)
		return (ft_putstr_fd("Failed to unlock table mutex\n", 2), false);
	return (true);
}

/**
 * @brief Starts the philosopher simulation.
 *
 * Locks the table mutex, creates all threads, waits for them to finish
 * (joining), and then marks the simulation as ended. Handles errors throughout
 * the process.
 *
 * @param table Pointer to the initialized table structure.
 * @return true if simulation runs and ends successfully, false otherwise.
 */
bool	dinner_init(t_table *table)
{
	unsigned int	i;

	if (table->shared->nbr_limit_meals == 0 || table->shared->philo_number == 0)
		return (true);
	if (pthread_mutex_lock(table->shared->table_mutex) != 0)
		return (ft_putstr_fd("Failed to lock table mutex\n", 2), false);
	if (!create_threads(table))
	{
		if (pthread_mutex_unlock(table->shared->table_mutex) != 0)
			return (ft_putstr_fd("Failed to unlock table mutex\n", 2), false);
		return (ft_putstr_fd("Failed to create threads\n", 2), false);
	}
	i = 0;
	while (i < table->shared->philo_number)
	{
		if (pthread_join(*table->philos[i].thread_id, NULL) != 0)
			return (printf("Failed to join thread"), false);
		i++;
	}
	if (!safe_set(&table->shared->end_simulation, &(bool){true}, table->shared->table_mutex, TYPE_BOOL))
		return (ft_putstr_fd("Failed to set end_simulation\n", 2), false);
	if (pthread_join(*table->monitor, NULL) != 0)
		return (ft_putstr_fd("Failed to join monitor thread\n", 2), false);
	return (true);
}
