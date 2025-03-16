# include "../inc/philo.h"

void wait_child(t_pid_list *head)
{
    int status;
    pid_t dead_philo;
    t_pid_list *node;
    
    dead_philo = waitpid(-1, &status, 0);
    if (dead_philo > 0)
    {
        node = find_node(head, dead_philo);
        printf("Philosopher %d has died\n", node->id);
        while (head)
        {
            if (head->pid != dead_philo)
                kill(head->pid, SIGTERM); 
            head = head->next;
        }
        exit(0);
    }
}

void handle_child_process(int id)
{
    printf("Child Process %d started\n", id); // ID starts at 1
    usleep(1000);
    exit(0);
}

static void table_init(t_table *table)
{
    table->console_sem = sem_open("/console_sem", O_CREAT, 0644, 1);
    if (table->console_sem == SEM_FAILED)
        handle_sem_error(errno, CREATE);
    table->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, table->philo_number);
    if (table->forks_sem == SEM_FAILED)
        handle_sem_error(errno, CREATE);
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
    while (i < table->philo_number)
    {
        pid = fork();
        if (pid < 0)
            error_exit("Fork error", "table_init");
        if (pid == 0)
            handle_child_process(i + 1);
        else 
            pid_list_append(&head, pid, i + 1);
        i++;
    }
    while (1)
        wait_child(head);
}
