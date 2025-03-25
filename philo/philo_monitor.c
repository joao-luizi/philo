/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:17 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/25 12:00:19 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/message.h"
#include "inc/philo.h"

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
		if (*local_end_simulation)
			return (true);
		if (check_philo_died(table, i))
			return (true);
		i++;
	}
	return (false);
}

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
