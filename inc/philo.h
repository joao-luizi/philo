# ifndef PHILO_H
#define PHILO_H

# include "defines.h"
# include "structs.h"

//aux.c
void error_exit(const char *error, char *function_name);
void *safe_malloc(size_t bytes);
t_table *get_table(char **argv);
long get_time(t_time_code timecode);

//parser/custom_atol.c
long custom_atol(const char *str);
//parser/parser.c
void parse_input(t_table *table, char **argv);
//mutex/error_handler.c
void safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
//mutex/safe_accessors.c
bool get_bool(t_mtx *mutex, bool *dest);
void set_bool(t_mtx *mutex, bool *dest, bool value);
long get_long(t_mtx *mutex, long *dest);
void set_long(t_mtx *mutex, long *dest, long value);
//threads/error_handler.c
void safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
//threads/synchronization.c
void wait_all_threads(t_table *table);
//init.c
void data_init(t_table *table);


#endif