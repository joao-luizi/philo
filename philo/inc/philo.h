/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:19:37 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 13:39:45 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "defines.h"
# include "structs.h"

// mutex/error_handler.c
bool	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
// mutex/safe_accessors.c
bool	get_bool(t_mtx *mutex, bool *dest);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
long	get_long(t_mtx *mutex, long *dest);
void	set_long(t_mtx *mutex, long *dest, long value);
void	increase_long(t_mtx *mutex, long *dest);

// parser/custom_atol.c
long	custom_atol(const char *str, bool *error);
// parser/parser.c
bool	parse_input(t_table *table, char **argv, int argc);

// philo/philo.c
bool	philo_init(t_table *table);
bool	philo_died(t_philo *philo, t_table *table);
void	philo_eat(t_philo *philo, t_table *table);
void	philo_think(t_philo *philo, t_table *table);

// table/table.c
bool	dinner_init(t_table *table);
void	*dinner_simulation(void *data);
void	*monitor_dinner(void *data);

//table/table_aux.
bool	table_init(t_table *table);
void	de_sync_philos(t_philo *philo, t_table *table);
void	*lone_philo(void *data);

// threads/error_handler.c
bool	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
			t_opcode opcode);
// threads/threads_aux.c
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);

// threads/write_output.c
void	write_status(t_status status, t_philo *philo, t_table *table);
// threads/write_aux.c
void	write_dead(t_philo *philo, long elapsed);
void	write_thinking(t_philo *philo, long elapsed);
void	write_sleeping(t_philo *philo, long elapsed);
void	write_eating(t_philo *philo, long elapsed);
void	write_take_fork(t_philo *philo, long elapsed);

// philo_aux.c
void	ft_putstr_fd(const char *s, int fd);
long	get_time(t_time_code timecode);
void	custom_usleep(long usec, t_table *table);
// philo.c
void	*safe_malloc(size_t bytes);
void	clean(t_table *table);

#endif