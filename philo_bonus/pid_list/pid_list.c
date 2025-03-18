# include "../inc/philo.h"

void free_pid_list(t_pid_list *head)
{
    t_pid_list *current = head;
    t_pid_list *next;

    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
}
t_pid_list *find_node(t_pid_list *head, pid_t pid)
{
    t_pid_list *current = head;

    while (current)
    {
        if (current->pid == pid)
            return current;
        current = current->next;
    }
    return NULL;
}

t_pid_list *pid_list_new(pid_t pid, int id, t_table *table)
{
    t_pid_list *new = malloc(sizeof(t_pid_list));
    if (!new)
        error_exit("Malloc error", "pid_list_new", table);

    new->pid = pid;
    new->id = id;
    new->next = NULL;

    return new;
}

void pid_list_append(t_pid_list **head, pid_t pid, int id, t_table *table)
{
    t_pid_list *last = *head;

    if (!last)
    {
        *head = pid_list_new(pid, id, table);
        return;
    }

    while (last->next)
        last = last->next;

    last->next = pid_list_new(pid, id, table);
}


