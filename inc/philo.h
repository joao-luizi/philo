# ifndef PHILO_H
#define PHILO_H

# include "defines.h"
# include "structs.h"


//mutex/error_handler.c
void safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
//mutex/safe_accessors.c
bool get_bool(t_mtx *mutex, bool *dest);
void set_bool(t_mtx *mutex, bool *dest, bool value);
long get_long(t_mtx *mutex, long *dest);
void set_long(t_mtx *mutex, long *dest, long value);
void increase_long(t_mtx *mutex, long *dest);

//parser/custom_atol.c
long custom_atol(const char *str);
//parser/parser.c
void parse_input(t_table *table, char **argv);

//philo/philo.c
bool philo_died(t_philo *philo, t_table *table);
void philo_eat(t_philo *philo);
void philo_think(t_philo *philo);
void philo_init(t_table *table);

//table/table.c
void table_init(t_table *table);

//threads/error_handler.c
void safe_sem_handle(sem_t *sem, const char *name, t_opcode opcode);
//threads/write_output.c
void write_status(int id, t_status status);
//threads/write_aux.c
void write_dead(int id, long elapsed);
void write_thinking(int id, long elapsed);
void write_sleeping(int id, long elapsed);
void write_eating(int id, long elapsed, long meal_counter);
void write_take_fork(int id, long elapsed, t_status status);

//philo_aux.c
long get_time(t_time_code timecode);
void custom_usleep(long usec, t_table *table);
//philo.c
void error_exit(const char *error, char *function_name);
void *safe_malloc(size_t bytes);
t_table *get_table(char **argv);
void clean(t_table *table);

#endif