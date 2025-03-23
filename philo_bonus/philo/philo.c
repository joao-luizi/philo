/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:15:53 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/23 18:48:51 by joaomigu         ###   ########.fr       */
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
	long	elapsed;
	long	time_to_die;
	long	last_meal_time;

	if (get_bool(philo->philo_semaphore, table, &philo->full))
		return (false);
	last_meal_time = get_long(philo->philo_semaphore,table, &philo->last_meal_time);
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
	if (table->philo_number % 2 == 0 || table->philo_number >= 100)
		return ;
	usleep(table->time_to_think * 0.2);
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
	safe_sem_handle(&table->forks, NULL, SEM_LOCK, table);
	write_status(TAKE_FIRST_FORK, philo, table);
	safe_sem_handle(&table->forks, NULL, SEM_LOCK, table);
	write_status(TAKE_SECOND_FORK, philo, table);
	set_long(philo->philo_semaphore, table, &philo->last_meal_time, get_time(MILLISECOND));
	philo->meal_counter++;
	write_status(EATING, philo, table);
	usleep(table->time_to_eat);
	if (table->nbr_limit_meals > 0
		&& philo->meal_counter == table->nbr_limit_meals)
		set_bool(philo->philo_semaphore, table, &philo->full, true);
	safe_sem_handle(&table->forks, NULL, SEM_UNLOCK, table);
	safe_sem_handle(&table->forks, NULL, SEM_UNLOCK, table);
}


static void set_philo_defaults(t_philo *philo, int id, t_table *table)
{
	philo->meal_counter = 0;
	philo->last_meal_time = 0;
	philo->full = false;
	philo->dead = false;
	philo->id = id;
	philo->table = table;
}
bool	philo_init(t_table *table)
{
	int		i;

	i = -1;
	set_long(table->table_semaphore, table, &table->start_simulation, get_time(MILLISECOND));
	while (++i < table->philo_number)
	{
		set_philo_defaults(&table->philos[i], i + 1, table);
        table->philos[i].process_id = fork();
        if (table->philos[i].process_id < 0)
            return (false);
        if (table->philos[i].process_id == 0)
            philo_routine(table->philos[i]);
	}
	return (true);
}
