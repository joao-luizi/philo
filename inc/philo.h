# ifndef PHILO_H
#define PHILO_H

# include "defines.h"
# include "structs.h"


//parser/custom_atol.c
long custom_atol(const char *str);
//parser/parser.c
void parse_input(t_table *table, char **argv);
//pid_list/pid_list.c
t_pid_list *find_node(t_pid_list *head, pid_t pid);
t_pid_list *pid_list_new(pid_t pid, int id);
void pid_list_append(t_pid_list **head, pid_t pid, int id);
//semaphores/error_handler.c
void safe_sem_handle(sem_t *sem, const char *name, t_opcode opcode);
void handle_sem_error(int status, t_opcode opcode);
//table/table.c
void start_dinner(t_table *table);
//write/write_output.c
void write_status(int id, t_status status);
//write/write_aux.c
void write_dead(int id, long elapsed);
void write_thinking(int id, long elapsed);
void write_sleeping(int id, long elapsed);
void write_eating(int id, long elapsed);
void write_take_fork(int id, long elapsed, t_status status);
//philo_aux.c
long get_time(t_time_code timecode);
void custom_usleep(long usec);
//philo.c
void error_exit(const char *error, char *function_name);
void *safe_malloc(size_t bytes);
t_table *get_table(char **argv);
void clean(t_table *table);

#endif