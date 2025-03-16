# include "../inc/philo.h"




void table_init(t_table *table)
{
    pid_t pid;
    int i = 0;

    // Initialize semaphores
    sem_init(&table->end_simulation, 1, 1); // Binary semaphore
    sem_init(&table->console_sem, 1, 1);    // Binary semaphore
    sem_init(&table->forks_sem, 1, table->philo_number); // Counting semaphore

    // Allocate memory for storing PIDs
    table->pids = malloc(sizeof(pid_t) * table->philo_number);
    if (!table->pids)
        error_exit("Malloc error", "table_init");

    // Fork philosophers
    while (i < table->philo_number)
    {
        pid = fork();
        if (pid < 0)
            error_exit("Fork error", "table_init");

        if (pid == 0) // Child process
        {
            printf("Child Process %d started\n", i + 1); // ID starts at 1

            usleep(1000);
            exit(0);
        }
        else // Parent process
        {
            table->pids[i] = pid; // Store philosopher PID
        }
        i++;
    }

    // Wait for any philosopher to die
    while (1)
    {
        int status;
        pid_t dead_philo = waitpid(-1, &status, 0);
        
        if (dead_philo > 0) // A philosopher exited
        {
            printf("Philosopher %d has died\n", dead_philo);
            for (int j = 0; j < table->philo_number; j++)
            {
                kill(table->pids[j], SIGTERM); // Kill all remaining processes
            }
            break;
        }
    }
}