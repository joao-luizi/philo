/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:49:10 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/26 12:31:38 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/message.h"
#include "inc/philo.h"

static bool	create_parent_monitor(t_table *table)
{
    unsigned int i;
    
    if (pthread_create(table->parent_monitor_thread, NULL, death_monitor_thread, table) != 0)
        return (ft_putstr_fd("Failed to create death monitor thread\n", 2), false);
    pthread_detach(*table->parent_monitor_thread);
    if (sem_post(table->shared->start_semaphore) != 0)
        return (ft_putstr_fd("Failed to unlock start_semaphore\n", 2), false);
    i = 0;
    while (i < table->shared->philo_number)
    {
        if (waitpid(table->philos[i].process_id, NULL, 0) < 0)
            return (ft_putstr_fd("Failed to wait on process\n", 2), false);
        i++;
    }
    usleep(1000);
    return (true);
}

static bool	fork_philosophers(t_table *table)
{
    unsigned int	i;

    table->shared->start_simulation = get_time(MILLISECOND);
    i = 0;
    while (i < table->shared->philo_number)
    {
        table->philos[i].process_id = fork();
        if (table->philos[i].process_id < 0)
            return (ft_putstr_fd("Failed to fork process\n", 2), false);
        if (table->philos[i].process_id == 0)
            philo_life(&table->philos[i]);
        i++;
    }
    return (true);
}

bool	dinner_init(t_table *table)
{
    if (table->shared->nbr_limit_meals == 0 || table->shared->philo_number == 0)
        return (true);
    if (!fork_philosophers(table))
        return (false);
    if (!create_parent_monitor(table))
        return (false);
    return (true);
}

static void set_defaults(t_table *table, unsigned int i)
{
    table->philos[i].id = i + 1;
    table->philos[i].meal_counter = 0;
    table->philos[i].last_meal_time = 0;
    table->philos[i].full = false;
    table->philos[i].shared = table->shared;
    table->philos[i].process_id = 0;
}
bool	table_init(t_table *table)
{
    unsigned int	i;
	
    table->philos = ft_calloc(table->shared->philo_number * sizeof(t_philo));
    if (!table->philos)
        return (ft_putstr_fd("Failed to allocate memory for philosophers\n", 2), false);
    table->parent_monitor_thread = ft_calloc(sizeof(pthread_t));
    if (!table->parent_monitor_thread)
        return (ft_putstr_fd("Failed to allocate memory for parent monitor thread\n", 2), false);
    i = 0;
    while (i < table->shared->philo_number)
    {
        set_defaults(table, i);
        table->philos[i].philo_semaphore = ft_calloc(sizeof(sem_t));
        if (!table->philos[i].philo_semaphore || sem_init(table->philos[i].philo_semaphore, 0, 1) != 0)
            return (ft_putstr_fd("Failed to initialize philo semaphore\n", 2), false);
        table->philos[i].monitor_thread = ft_calloc(sizeof(pthread_t));
        if (!table->philos[i].monitor_thread)
            return (ft_putstr_fd("Failed to allocate memory for monitor thread\n", 2), false);
        i++;
    }
    return (true);
}
