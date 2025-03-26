/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:03:21 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/26 13:56:54 by joaomigu         ###   ########.fr       */
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
no one should die, unless the cluster is crowded

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

static void	display_arg_error(void)
{
	printf(R "Wrong input\n" G "Example usage: ./philo (number of philosophers) (time to die) (time to eat)\
 (time to sleep) [number of meals]\n ./philo 5 800 200 200\n() - required []\
 - optional" RST);
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
	t_table	*table;
	bool	error;

	if (argc != 5 && argc != 6)
		return (display_arg_error(), 1);
	table = ft_calloc(sizeof(t_table));
	if (!table)
		return (ft_putstr_fd("Failed to allocate memory for table\n", 2), 1);
	table->shared = ft_calloc(sizeof(t_shared));
	if (!table->shared)
	{
		free(table);
		return (ft_putstr_fd("Failed to allocate memory for shared\n", 2), 1);
	}
	error = parse_input(table->shared, argv, argc);
	if (!error)
		error = table_init(table);
	if (!error)
		error = dinner_init(table);
	clean_table(&table);
	if (error)
		return (1);
	return (0);
}
