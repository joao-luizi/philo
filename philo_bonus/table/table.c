# include "../inc/philo.h"

void handle_exit(t_table *table, t_pid_list *head, pid_t dead_philo, t_pid_list *node)
{
    write_status(node->id, DEAD, table);
    while (head)
    {
        if (head->pid != dead_philo)
            kill(head->pid, SIGTERM);
        head = head->next;
    }
    exit(0);
}
void wait_child(t_pid_list *head, t_table *table)
{
    int status;
    pid_t dead_philo;
    t_pid_list *node;
    int exit_code;

    while (1)
    {
        dead_philo = waitpid(-1, &status, 0);
        if (dead_philo < 0 && errno == ECHILD)
            break;
        node = find_node(head, dead_philo);
        if (!node)
            error_exit("dead_philo NULL node", "wait_child @ table.c", table);
        if (WIFEXITED(status))
        {
            exit_code = WEXITSTATUS(status);
            if (exit_code > 0)
                handle_exit(table, head, dead_philo, node);
        }
    }
}

void handle_lone_philo(t_table *table)
{
    long last_meal = table->start_simulation;
    write_status(1, TAKE_FIRST_FORK, table);
    while (!philo_dead(table, last_meal, table->time_to_die))
        custom_usleep(10, table);
    write_status(1, DEAD, table);
    exit(0);
}
void handle_child_process(int id, t_table *table)
{
    long last_meal = table->start_simulation;
    long meal_counter = 0;
    if (id % 2 == 0)
        philo_think(table, &last_meal, id);
    while (!philo_dead(table, last_meal, table->time_to_die))
    {
        philo_eat(table, &last_meal, id, &meal_counter);
        if (philo_full(meal_counter, table->nbr_limit_meals))
            exit(0);
        philo_sleep(table, &last_meal, id);
        philo_think(table, &last_meal, id);
    }
    exit(1);
}

void start_dinner(t_table *table)
{
    pid_t pid;
    t_pid_list *head;
    int i;

    i = 0;
    head = NULL;
    table->start_simulation = get_time(MILLISECOND, table);
    if (table->philo_number == 1)
        handle_lone_philo(table);
    while (i < table->philo_number)
    {
        pid = fork();
        if (pid < 0)
            error_exit("Fork error", "table_init", table);
        if (pid == 0)
            handle_child_process(i + 1, table);
        else 
            pid_list_append(&head, pid, i + 1, table);
        i++;
    }
    wait_child(head, table);
    free_pid_list(head);
}
