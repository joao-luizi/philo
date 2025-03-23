/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 19:10:51 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/23 19:10:53 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "defines.h"
# include "structs.h"

// philo/philo.c
bool	philo_init(t_table *table);
bool	philo_died(t_philo *philo, t_table *table);
void	philo_eat(t_philo *philo, t_table *table);
void	philo_think(t_philo *philo, t_table *table);

// sem/safe_accessors.c
bool	get_bool(sem_t *sem, t_table *table, bool *dest);
void	set_bool(sem_t *sem, t_table *table, bool *dest, bool value);
long	get_long(sem_t *sem, t_table *table, long *dest);
void	set_long(sem_t *sem, t_table *table, long *dest, long value);
void	increase_long(sem_t *sem, t_table *table, long *dest);

// sem/error_handler.c
void	safe_sem_handle(sem_t **sem, const char *name, t_sem_action opcode,
			t_table *table);
// parser/custom_atol.c
long	custom_atol(const char *str, bool *error);
// parser/parser.c
bool	parse_input(t_table *table, char **argv, int argc);
// table/table.c
void	*monitor_routine(void *arg);
void	philo_routine(t_philo philo);
bool	dinner_init(t_table *table);
// table/table_aux.c
void	de_sync_philos(t_philo *philo, t_table *table);
bool	table_init(t_table *table);

// threads/write_output.c
void	write_status(t_status status, t_philo *philo, t_table *table);

// threads/error_handler.c
bool	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
			t_opcode opcode);

// philo_aux.c
void	error_exit(const char *message, t_table *table);
void	ft_putstr_fd(const char *s, int fd);
long	get_time(t_time_code timecode);
// philo.c
void	*safe_malloc(size_t bytes);
void	clean(t_table *table);

#endif