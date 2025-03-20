# ifndef PHILO_H
#define PHILO_H

# include "defines.h"
# include "structs.h"

//philo/philo.c
bool	philo_init(t_table *table);
//sem/safe_accessors.c
bool	get_bool(sem_t *sem, t_table *table, bool *dest);
void	set_bool(sem_t *sem, t_table *table, bool *dest, bool value);
long	get_long(sem_t *sem, t_table *table, long *dest);
void	set_long(sem_t *sem, t_table *table, long *dest, long value);
void	increase_long(sem_t *sem, t_table *table, long *dest);

//sem/safe_sem_handle.c
void safe_sem_handle(sem_t **sem, const char *name, t_sem_action opcode, t_table *table);
// parser/custom_atol.c
long	custom_atol(const char *str, bool *error);
// parser/parser.c
bool	parse_input(t_table *table, char **argv, int argc);
//table/table.c
void	de_sync_philos(t_philo *philo, t_table *table);
bool	table_init(t_table *table);

//threads/write_output.c
void	write_status(t_status status, t_philo *philo, t_table *table);
//threads/write_aux.c
void	write_dead(t_philo *philo, long elapsed);
void	write_thinking(t_philo *philo, long elapsed);
void	write_sleeping(t_philo *philo, long elapsed);
void	write_eating(t_philo *philo, long elapsed);
void	write_take_fork(t_philo *philo, long elapsed);
//threads/error_handler.c
bool	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

// philo_aux.c
void 	error_exit(const char *message, t_table *table);
void	ft_putstr_fd(const char *s, int fd);
long	get_time(t_time_code timecode);
void	custom_usleep(long usec, t_table *table);
// philo.c
void	*safe_malloc(size_t bytes);
void	clean(t_table *table);

#endif