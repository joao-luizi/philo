/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:03:21 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 11:16:09 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

/*
5 800 200 200
no one should die
5 600 150 150
no one should die
4 410 200 200
no one should die
100 800 200 200
no one should die
105 800 200 200
no one should die
200 800 200 200
no one should die

1 800 200 200
a philo should die
4 310 200 100
a philo should die
4 200 205 200
a philo should die
5 800 200 200 7
no one should die, simulation should stop after 7 eats
4 410 200 200 10
no one should die, simulation should stop after 10 eats
-5 600 200 200
should error and not run (no crashing)
4 -5 200 200
should error and not run (no crashing)
4 600 -5 200
should error and not run (no crashing)
4 600 200 -5
should error and not run (no crashing)
4 600 200 200 -5
should error and not run (no crashing)
*/

/**
 * @brief Cleans up resources used by the table.
 * 
 * This function destroys all mutexes associated with 
 * philosophers and forks,
 * then frees the memory allocated for the philosophers 
 * and forks.
 * 
 * @param table The table to clean up.
 */
void	clean(t_table *table)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = 0;
	while (i < table->philo_number)
	{
		philo = table->philos + i;
		fork = table->forks + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
		safe_mutex_handle(&fork->fork, DESTROY);
		i++;
	}
	safe_mutex_handle(&table->write_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}

/**
 * @brief Allocates memory safely.
 * 
 * This function allocates memory using malloc, checks for 
 * allocation errors,
 * and initializes the allocated memory to zero.
 * 
 * @param bytes The number of bytes to allocate.
 * @return A pointer to the allocated memory, or NULL if 
 * allocation failed.
 */
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		printf(R "Error on memory allocation\n" RST);
		return (NULL);
	}
	memset(ret, 0, bytes);
	return (ret);
}

/**
 * @brief The main entry point of the program.
 * 
 * This function initializes the table, parses the input arguments, 
 * and starts
 * the dinner simulation. If any errors occur during initialization 
 * or simulation,
 * it cleans up resources and returns an error code.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return An error code (0 for success, 1 for failure).
 */
int	main(int argc, char **argv)
{
	t_table	table;
	bool	error;

	error = false;
	if (argc == 5 || argc == 6)
	{
		if (!parse_input(&table, argv, argc))
			return (1);
		error = !table_init(&table);
		if (!error)
			error = !philo_init(&table);
		if (!error)
			error = !dinner_init(&table);
		clean(&table);
	}
	else
	{
		printf(R "Wrong input\n" G "Example usage: ./philo (number of philosophers) (time to die) (time to eat) \
            (time to sleep) [number of meals]\n ./philo 5 800 200 200\n()\
	- required [] - optional" RST);
		return (1);
	}
	return (0);
}
