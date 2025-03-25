/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:19:37 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/25 12:08:46 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "defines.h"
# include "structs.h"

// mutex_helpers.c
bool			safe_get(void *dest, void *src, pthread_mutex_t *mutex,
					t_type type);
bool			safe_set(void *dest, void *src, pthread_mutex_t *mutex,
					t_type type);
bool			safe_increase(void *dest, pthread_mutex_t *mutex, t_type type);
// parser
bool			parse_input(t_shared *shared, char **argv, int argc);
unsigned int	custom_atol(const char *str, bool *error);
// philo_aux.c
void			ft_putstr_fd(const char *s, int fd);
void			*ft_calloc(size_t bytes);
unsigned int	get_time(t_time_code timecode);
void			custom_sleep(unsigned int sleep_time_ms, t_shared *shared);
// philo_life.c
bool			write_states(t_status status, t_philo *philo);
void			*philo_life_single(void *args);
void			*philo_life_many(void *args);
// philo_mem.c
void			clean_table(t_table **table);
// philo_monitor.c
void			*monitor(void *args);
// philo_states.c
bool			philo_died(t_philo *philo);
void			philo_think(t_philo *philo);
bool			philo_eat(t_philo *philo, t_shared *shared);
// table.c
bool			table_init(t_table *table);
bool			dinner_init(t_table *table);

#endif