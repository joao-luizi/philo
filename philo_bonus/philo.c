# include "inc/philo.h"
void clean(t_table *table)
{
    safe_sem_handle(table->console_sem, "/console_sem", UNLINK);
    safe_sem_handle(table->forks_sem, "/forks_sem", UNLINK);
    safe_sem_handle(table->end_simulation, "/end_simulation", UNLINK);
    if (table->pids)
        free(table->pids);
}


static void table_init(t_table *table)
{
    safe_sem_handle(table->console_sem, "/console_sem", UNLINK);
    table->console_sem = sem_open("/console_sem", O_CREAT, 0644, 1);
    if (table->console_sem == SEM_FAILED)
        handle_sem_error(errno, CREATE);
    safe_sem_handle(table->forks_sem, "/forks_sem", UNLINK);
    table->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, table->philo_number);
    if (table->forks_sem == SEM_FAILED)
        handle_sem_error(errno, CREATE);
    safe_sem_handle(table->end_simulation, "/end_simulation", UNLINK);
    table->end_simulation = sem_open("/end_simulation", O_CREAT, 0644, 1);
    if (table->end_simulation == SEM_FAILED)
        handle_sem_error(errno, CREATE);
    table->start_simulation = get_time(MILLISECOND);

}

void error_exit(const char *error, char *function_name, t_table *table)
{
    if (DEBUG)
        printf(R "%s (%s)\n" RST, error, function_name);
    else
        printf(R "%s \n" RST, error);
    clean(table);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    t_table table;
    if (argc == 5 || argc == 6)
    {
        parse_input(&table, argv);
        table_init(&table);
        start_dinner(&table);
        clean(&table);
    }
    else
        error_exit("Wrong input\n"\
            G"Example usage: ./philo (number of philosophers) \
(time to die) (time to eat) (time to sleep) [number of meals]\n\
./philo 5 800 200 200\n\
() - required [] - optional"RST, "main @ philo.c", &table);
    return (0);
}