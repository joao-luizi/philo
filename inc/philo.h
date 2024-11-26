# ifndef PHILO_H
#define PHILO_H

# include "defines.h"
# include "structs.h"

//aux.c
void error_exit(const char *error);

//parser/custom_atol.c
long custom_atol(const char *str);
//parser/parser.c
void parse_input(t_table *table, char **argv);
#endif