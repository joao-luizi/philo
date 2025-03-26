/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:17:17 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/26 13:53:57 by joaomigu         ###   ########.fr       */
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

static bool	set_defaults_aux(t_shared *shared)
{
	sem_unlink("/write_semaphore");
	shared->write_semaphore = sem_open("/write_semaphore", O_CREAT | O_EXCL,
			0644, 1);
	if (shared->write_semaphore == SEM_FAILED)
		return (ft_putstr_fd("Failed write_semaphore\n", 2), false);
	sem_unlink("/forks_semaphore");
	shared->forks_semaphore = sem_open("/forks_semaphore", O_CREAT | O_EXCL,
			0644, shared->philo_number);
	if (shared->forks_semaphore == SEM_FAILED)
		return (ft_putstr_fd("Failed forks_semaphore\n", 2), false);
	sem_unlink("/death_semaphore");
	shared->death_semaphore = sem_open("/death_semaphore", O_CREAT | O_EXCL,
			0644, 0);
	if (shared->death_semaphore == SEM_FAILED)
		return (ft_putstr_fd("Failed death_semaphore\n", 2), false);
	return (true);
}

static bool	set_defaults(t_shared *shared)
{
	shared->start_simulation = 0;
	shared->end_simulation = false;
	if ((shared->time_to_eat * 2) < shared->time_to_sleep)
		shared->time_to_think = 0;
	else
		shared->time_to_think = (shared->time_to_eat * 2)
			- shared->time_to_sleep;
	sem_unlink("/start_semaphore");
	shared->start_semaphore = sem_open("/start_semaphore", O_CREAT | O_EXCL,
			0644, 0);
	if (shared->start_semaphore == SEM_FAILED)
		return (ft_putstr_fd("Failed start_semaphore\n", 2), false);
	sem_unlink("/table_semaphore");
	shared->table_semaphore = sem_open("/table_semaphore", O_CREAT | O_EXCL,
			0644, 1);
	if (shared->table_semaphore == SEM_FAILED)
		return (ft_putstr_fd("Failed table_semaphore\n", 2), false);
	return (set_defaults_aux(shared));
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
