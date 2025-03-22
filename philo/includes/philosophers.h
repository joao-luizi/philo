/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:28:43 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/23 13:57:58 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>

# define ARG_NBR_ERROR "Wrong number of arguments.\n"
# define INV_ARG_ERROR "Invalid arguments.\n"

# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define SATISFIED 4
# define DEAD 5

# define SIM_START "---------------------------------------\n\
|   \033[35mTIME\033[0m   | \033[35mPHILO\033[0m |      \033[35mEVENT\033[0m       |\n\
---------------------------------------\n"

# define SIM_END "---------------------------------------\n"

# define MSG_FORK "|\033[36m%10ld\033[0m|%4d   | \
\033[33mhas taken a fork\033[0m |\n"
# define MSG_EATING "|\033[36m%10ld\033[0m|%4d   |    \
\033[33mis eating\033[0m     |\n"
# define MSG_SLEEPING "|\033[36m%10ld\033[0m|%4d   |   \
\033[33mis sleeping\033[0m    |\n"
# define MSG_THINKING "|\033[36m%10ld\033[0m|%4d   |   \
\033[33mis thinking\033[0m    |\n"
# define MSG_SATISFIED "|\033[36m%10ld\033[0m|   \
\033[32mall philos satisfied\033[0m   |\n"
# define MSG_DEAD "|\033[36m%10ld\033[0m|%4d   |       \
\033[31mdied\033[0m       |\n"

typedef struct s_info
{
	suseconds_t		start_time;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				philo_satisfied;
	int				finish_sim;
	pthread_t		verify_death;
	pthread_mutex_t	*monitor;
}				t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				times_eaten;
	suseconds_t		last_meal;
	t_info			*info;
}				t_philo;

// Error handling

int				argument_number_error(void);
int				inv_argument_error(void);

// Data initialization

void			info_init(t_info *info, int argc, char **argv);
pthread_mutex_t	*fork_init(t_info *info);
t_philo			*philos_init(t_info *info, pthread_mutex_t *fork_mutex);
void			philo_info_init(t_info *info, t_philo *philo,
					pthread_mutex_t *fork_mutex, int philo_id);
void			*threads_init(t_philo *philos);

// Cleanup

void			clean_sim(pthread_mutex_t *fork_mutex, t_philo *philos);

// Main routine

void			*philo_func(void *philo);
void			*single_philo(t_philo *philo);
void			grab_forks(t_philo *philo);
void			eating_sleeping(t_philo *philo);
void			drop_forks(t_philo *philo);

// Simulation termination checker

void			*death_check(void *philo);
void			eat_check(t_philo *philos);
void			*finish_sim(t_philo *philos);

// Utility functions

int				args_check(char **argv);
int				ft_atoi(const char *str);
void			log_state(int state, t_philo *philo);
void			in_action(t_philo *philo, suseconds_t time_to_wait);
suseconds_t		gettimems(void);

#endif