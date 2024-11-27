# ifndef PHILO_H
#define PHILO_H

# include "defines.h"
# include "structs.h"

//aux.c
void error_exit(const char *error);
void *safe_malloc(size_t bytes);

//parser/custom_atol.c
long custom_atol(const char *str);
//parser/parser.c
void parse_input(t_table *table, char **argv);
//mutex/error_handler.c
void safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
//thread/error_handler.c
void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
//init.c
void data_init(t_table *table);
#endif