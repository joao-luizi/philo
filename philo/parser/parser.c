/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:17:17 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/25 12:33:09 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/message.h"
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
static bool	extra_errors(t_shared *shared)
{
	if (shared->philo_number == 0)
		return (ft_putstr_fd(R NO_P RST, 2), true);
	if (shared->philo_number > 200)
		return (ft_putstr_fd(R TOO_MANY_P RST, 2), true);
	if (shared->time_to_die == 0)
		return (ft_putstr_fd(R TT_DIE RST, 2), true);
	if (shared->time_to_eat == 0)
		return (ft_putstr_fd(R TT_EAT RST, 2), true);
	if (shared->time_to_sleep == 0)
		return (ft_putstr_fd(R TT_SLEEP RST, 2), true);
	return (false);
}

static bool	set_defaults(t_shared *shared)
{
	shared->start_simulation = 0;
	shared->end_simulation = false;
	if (((shared->time_to_eat * 2) < shared->time_to_sleep))
		shared->time_to_think = 0;
	else
		shared->time_to_think = (shared->time_to_eat * 2)
			- shared->time_to_sleep;
	shared->table_mutex = NULL;
	shared->write_mutex = NULL;
	shared->table_mutex = ft_calloc(sizeof(pthread_mutex_t));
	if (!shared->table_mutex || pthread_mutex_init(shared->table_mutex,
			NULL) != 0)
		return (printf("Failed to initialize table_mutex\n"), false);
	shared->write_mutex = ft_calloc(sizeof(pthread_mutex_t));
	if (!shared->write_mutex || pthread_mutex_init(shared->write_mutex,
			NULL) != 0)
		return (printf("Failed to initialize write_mutex\n"), false);
	return (true);
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
bool	parse_input(t_shared *shared, char **argv, int argc)
{
	bool	error;

	error = false;
	shared->philo_number = custom_atol(argv[1], &error);
	shared->time_to_die = custom_atol(argv[2], &error) * 1000;
	shared->time_to_eat = custom_atol(argv[3], &error) * 1000;
	shared->time_to_sleep = custom_atol(argv[4], &error) * 1000;
	if (argc == 6)
		shared->nbr_limit_meals = custom_atol(argv[5], &error);
	else
		shared->nbr_limit_meals = -1;
	if (error || extra_errors(shared))
		return (true);
	return (!set_defaults(shared));
}
