/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:06:11 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 00:15:12 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

void	de_sync_philos(t_philo *philo, t_table *table)
{
	if (table->philo_number % 2 == 0)
	{
		if (philo->id % 2 == 0)
			custom_usleep(30000, table);
	}
	else
	{
		if (philo->id % 2 == 0)
			philo_think(philo, table);
	}
}

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
