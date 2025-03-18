# ifndef PHILO_H
#define PHILO_H

# include "defines.h"
# include "structs.h"

bool philo_full(long meal_counter, long nbr_limit_meals);
bool philo_dead(t_table *table, long last_meal, long time_to_die);
void philo_eat(t_table *table, long *last_meal, int id, long *meal_counter);
void philo_think(t_table *table, long *last_meal, int id);
void philo_sleep(t_table *table, long *last_meal, int id);

//parser/custom_atol.c
long custom_atol(const char *str, t_table *table);
//parser/parser.c
void parse_input(t_table *table, char **argv);
//pid_list/pid_list.c
t_pid_list *find_node(t_pid_list *head, pid_t pid);
t_pid_list *pid_list_new(pid_t pid, int id, t_table *table);
void pid_list_append(t_pid_list **head, pid_t pid, int id, t_table *table);
void free_pid_list(t_pid_list *head);
//semaphores/error_handler.c
void safe_sem_handle(sem_t *sem, const char *name, t_opcode opcode, t_table *table);
void handle_sem_error(int status, t_opcode opcode, t_table *table);
//table/table.c
void start_dinner(t_table *table);
//write/write_output.c
void write_status(int id, t_status status, t_table *table);
//write/write_aux.c
void write_dead(int id, long elapsed);
void write_thinking(int id, long elapsed);
void write_sleeping(int id, long elapsed);
void write_eating(int id, long elapsed);
void write_take_fork(int id, long elapsed, t_status status);
//philo_aux.c
long get_time(t_time_code timecode, t_table *table);
void custom_usleep(long usec, t_table *table);
//philo.c
void error_exit(const char *error, char *function_name, t_table *table);
void clean(t_table *table);

#endif