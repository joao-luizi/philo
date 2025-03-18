# include "../inc/philo.h"

bool philo_full(long meal_counter, long nbr_limit_meals)
{
    if (nbr_limit_meals > 0)    
        return (meal_counter >= nbr_limit_meals);
    return (false);
}

bool philo_dead(long last_meal, long time_to_die)
{
    long time = get_time(MILLISECOND);
    long elapsed = time - last_meal;
    return (elapsed >= time_to_die);
}

void philo_eat(t_table *table, long *last_meal, int id, long *meal_counter)
{
    safe_sem_handle(table->forks_sem, NULL, LOCK);
    write_status(id, TAKE_FIRST_FORK);
    safe_sem_handle(table->forks_sem, NULL, LOCK);
    write_status(id, TAKE_SECOND_FORK);  
    *last_meal = get_time(MILLISECOND);
    if (table->nbr_limit_meals > 0)
        (*meal_counter)++;
    write_status(id, EATING);
    while (get_time(MILLISECOND) < *last_meal + table->time_to_eat)
    {
        if (philo_dead(*last_meal, table->time_to_die))
        {
            safe_sem_handle(table->forks_sem, NULL, UNLOCK);
            safe_sem_handle(table->forks_sem, NULL, UNLOCK);
            exit(1);
        }
        custom_usleep(10);
    }
    safe_sem_handle(table->forks_sem, NULL, UNLOCK);
    safe_sem_handle(table->forks_sem, NULL, UNLOCK);
}
void philo_think(t_table *table, long *last_meal, int id)
{
    long start = get_time(MILLISECOND);
    long time_to_think = (table ->time_to_die - table->time_to_eat - table->time_to_sleep) * 0.5;
    if (time_to_think < 0)
        time_to_think = 0;
    long end = start + time_to_think;
    write_status(id, THINKING);
    while (get_time(MILLISECOND) < end)
    {
        if (philo_dead(*last_meal, table->time_to_die))
            exit(1);
        custom_usleep(10);
    }
}
void philo_sleep(t_table *table, long *last_meal, int id)
{
    long start = get_time(MILLISECOND);
    long end = start + table->time_to_sleep;
    write_status(id, SLEEPING);
    while (get_time(MILLISECOND) < end)
    {
        if (philo_dead(*last_meal, table->time_to_die))
            exit(1);
        custom_usleep(10);
    }
}

void wait_child(t_pid_list *head)
{
    int status;
    pid_t dead_philo;
    t_pid_list *node;

    while (1)
    {
        dead_philo = waitpid(-1, &status, 0);
        if (dead_philo < 0)
        {
            if (errno == ECHILD)
                break;
        }
        node = find_node(head, dead_philo);
        if (!node)
            error_exit("dead_philo NULL node", "wait_child @ table.c");
        if (WIFEXITED(status))
        {
            int exit_code = WEXITSTATUS(status);
            if (exit_code > 0)
            {
                write_status(node->id, DEAD);
                while (head)
                {
                    if (head->pid != dead_philo)
                        kill(head->pid, SIGTERM);
                    head = head->next;
                }
                exit(0);
            }
        }
    }
}

void handle_lone_philo(t_table *table)
{
    long last_meal = table->start_simulation;
    write_status(1, TAKE_FIRST_FORK);
    while (!philo_dead(last_meal, table->time_to_die))
        custom_usleep(10);
    write_status(1, DEAD);
    exit(0);
}
void handle_child_process(int id, t_table *table)
{
    long last_meal = table->start_simulation;
    long meal_counter = 0;
    if (id % 2 == 0)
        philo_think(table, &last_meal, id);
    while (!philo_dead(last_meal, table->time_to_die))
    {
        philo_eat(table, &last_meal, id, &meal_counter);
        if (philo_full(meal_counter, table->nbr_limit_meals))
            exit(0);
        philo_sleep(table, &last_meal, id);
        philo_think(table, &last_meal, id);
    }
    exit(1);
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

void start_dinner(t_table *table)
{
    pid_t pid;
    t_pid_list *head;
    int i;

    i = 0;
    head = NULL;
    table_init(table);
    table->start_simulation = get_time(MILLISECOND);
    if (table->philo_number == 1)
        handle_lone_philo(table);
    while (i < table->philo_number)
    {
        pid = fork();
        if (pid < 0)
            error_exit("Fork error", "table_init");
        if (pid == 0)
            handle_child_process(i + 1, table);
        else 
            pid_list_append(&head, pid, i + 1);
        i++;
    }
    wait_child(head);
    free_pid_list(head);
}
