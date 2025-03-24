/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:15:53 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/24 14:51:14 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Checks if a philosopher has died.
 *
 * A philosopher is considered dead if the time elapsed since their 
 * last meal
 * exceeds the time to die.
 *
 * @param philo The philosopher to check.
 * @param table The table where the philosopher is sitting.
 *
 * @return true if the philosopher has died, false otherwise.
 */
bool	philo_died(t_philo *philo, t_table *table)
{
	unsigned int	elapsed;
	unsigned int	time_to_die;
	unsigned int	last_meal_time;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	last_meal_time = get_long(&philo->philo_mutex, &philo->last_meal_time);
	elapsed = get_time(MILLISECOND) - last_meal_time;
	time_to_die = table->time_to_die / 1000;
	return (elapsed >= time_to_die);
}

/**
 * @brief Simulates a philosopher thinking.
 *
 * If the number of philosophers at the table is even, the function 
 * returns
 * immediately. Otherwise, it simulates the thinking process by sleeping 
 * for a
 * fraction of the time to think.
 *
 * @param philo The philosopher who is thinking.
 * @param table The table where the philosopher is sitting.
 */
void	philo_think(t_philo *philo, t_table *table)
{
	write_status(THINKING, philo, table);
	if (table->philo_number % 2 == 0)
		return ;
	usleep(table->time_to_think * 0.4);
}

/**
 * @brief Simulates a philosopher eating.
 *
 * The philosopher attempts to acquire both their first and 
 * second forks. If
 * successful, they eat for the specified time and update their 
 * last meal time.
 * If the philosopher has reached the maximum number of meals, 
 * they are marked as
 * full.
 *
 * @param philo The philosopher who is eating.
 * @param table The table where the philosopher is sitting.
 */
void	philo_eat(t_philo *philo, t_table *table)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, table);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, table);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&philo->philo_mutex, &philo->meal_counter);
	//philo->meal_counter++;
	write_status(EATING, philo, table);
	usleep(table->time_to_eat);
	if (table->nbr_limit_meals > 0
		&& (int)philo->meal_counter == table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

/**
 * @brief Assigns forks to a philosopher.
 *
 * The assignment of forks depends on the philosopher's 
 * position at the table and
 * their ID. If the philosopher's ID is even, the first 
 * fork is assigned to the
 * current position and the second fork is assigned to the 
 * next position. If the
 * philosopher's ID is odd, the first fork is assigned to 
 * the next position and
 * the second fork is assigned to the current position.
 *
 * @param philo The philosopher to assign forks to.
 * @param forks The array of forks.
 * @param philo_pos The position of the philosopher at the table.
 */
static void	assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_number;

	philo_number = philo->table->philo_number;
	philo->first_fork = &forks[(philo_pos + 1) % philo_number];
	philo->second_fork = &forks[philo_pos];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_number];
	}
}

/**
 * @brief Initializes the philosophers at the table.
 *
 * Each philosopher is assigned an ID, marked as not full, and 
 * initialized with
 * a meal counter of 0. Their mutex is also initialized. The forks
 *  are assigned
 * to each philosopher using the assign_forks function.
 *
 * @param table The table where the philosophers are sitting.
 *
 * @return true if the initialization is successful, false otherwise.
 */
bool	philo_init(t_table *table)
{
	unsigned int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_number)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meal_counter = 0;
		philo->table = table;
		philo->last_meal_time = 0;
		philo->thread_id = 0;
		if (!safe_mutex_handle(&philo->philo_mutex, INIT))
			return (false);
		assign_forks(philo, table->forks, i);
		i++;
	}
	return (true);
}
