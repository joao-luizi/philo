/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:19:37 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/27 11:37:31 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "defines.h"
# include "structs.h"

// mutex_helpers.c
bool			safe_get(void *dest, void *src, sem_t *semaphore, t_type type);
bool			safe_set(void *dest, void *src, sem_t *semaphore, t_type type);
bool			safe_increase(void *dest, sem_t *semaphore, t_type type);
// parser/parser.c
bool			parse_input(t_shared *shared, char **argv, int argc);
// parser/custom_atol.c
unsigned int	custom_atol(const char *str, bool *error);
// philo_aux.c
void			*ft_calloc(size_t bytes);
void			ft_putstr_fd(const char *s, int fd);
unsigned int	get_time(t_time_code timecode);
void			custom_sleep(unsigned int sleep_time_ms);

// philo_life.c
void			philo_life(t_philo *philo);
bool			write_states(t_status status, t_philo *philo);
// philo_mem.c
void			clean_table(t_table **table);
// philo_monitor.c
void			*death_monitor_thread(void *arg);
void			*philosopher_monitor(void *arg);
// philo_states.c
bool			philo_died(t_philo *philo);
void			philo_think(t_philo *philo);
bool			philo_eat(t_philo *philo, t_shared *shared);
// table.c
bool			table_init(t_table *table);
bool			dinner_init(t_table *table);
#endif