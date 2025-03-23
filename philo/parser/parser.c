/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:17:17 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/23 18:59:04 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Checks for extra errors in the input table.
 *
 * This function checks if the number of philosophers, time to die, time to eat,
 * and time to sleep are valid (i.e., not zero). If any of these values are
 * zero, it prints an error message and returns true.
 *
 * @param table The input table to be checked.
 * @return true If an error is found, false otherwise.
 */
static bool	extra_errors(t_table *table)
{
	if (table->philo_number == 0)
	{
		ft_putstr_fd(R "Invalid Input: There must be at \
			least one philosopher\n" RST, STDERR_FILENO);
		return (true);
	}
	if (table->time_to_die == 0)
	{
		ft_putstr_fd(R "Invalid Input: time to die is 0\n" RST, STDERR_FILENO);
		return (true);
	}
	if (table->time_to_eat == 0)
	{
		ft_putstr_fd(R "Invalid Input: time to eat is 0\n" RST, STDERR_FILENO);
		return (true);
	}
	if (table->time_to_sleep == 0)
	{
		ft_putstr_fd(R "Invalid Input: time to sleep is \
			0\n" RST, STDERR_FILENO);
		return (true);
	}
	return (false);
}

/**
 * @brief Parses the input arguments and populates the table
 * structure.
 *
 * This function parses the input arguments and populates the
 * table structure
 * with the number of philosophers, time to die, time to eat,
 * time to sleep,
 * and the optional number of meals limit. It also checks for
 * errors in the
 * input values and returns false if any error is found.
 *
 * @param table The table structure to be populated.
 * @param argv The array of input arguments.
 * @param argc The number of input arguments.
 * @return true If the input is parsed successfully, false
 * otherwise.
 */
bool	parse_input(t_table *table, char **argv, int argc)
{
	bool	error;

	error = false;
	table->philo_number = custom_atol(argv[1], &error);
	table->time_to_die = custom_atol(argv[2], &error) * 1000;
	table->time_to_eat = custom_atol(argv[3], &error) * 1000;
	table->time_to_sleep = custom_atol(argv[4], &error) * 1000;
	table->forks = NULL;
	table->philos = NULL;
	if (argc == 6)
		table->nbr_limit_meals = custom_atol(argv[5], &error);
	else
		table->nbr_limit_meals = -1;
	if (error || extra_errors(table))
		return (false);
	table->time_to_think = (table->time_to_eat * 2) - table->time_to_sleep;
	if (table->time_to_think < 0)
		table->time_to_think = 0;
	else if (table->time_to_think > table->time_to_sleep)
		table->time_to_think = table->time_to_sleep;
	return (true);
}
