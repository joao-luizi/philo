# ifndef PHILO_H
#define PHILO_H

# include "defines.h"
# include "structs.h"

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

// philo_aux.c
void 	error_exit(const char *message, t_table *table);
void	ft_putstr_fd(const char *s, int fd);
long	get_time(t_time_code timecode);
void	custom_usleep(long usec, t_table *table);
// philo.c
void	*safe_malloc(size_t bytes);
void	clean(t_table *table);

#endif