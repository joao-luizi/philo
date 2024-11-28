# include "../inc/philo.h"


static void assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
    int philo_number;

    philo_number = philo->table->philo_number;
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &forks[philo_pos];
        philo->second_fork= &forks[philo_pos + 1 % philo_number];
    }
    else
    {
        philo->second_fork= &forks[philo_pos + 1 % philo_number];
        philo->first_fork = &forks[philo_pos];
    }
}
static void philo_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = 0;
    while (i <table->philo_number)
    {
        philo = &table->philos[i];
        philo->id = i + 1;
        philo->full = false;
        philo->meal_counter = 0;
        philo->table = table;
        assign_forks(philo, table->forks, i);
        i++;
    }
}
void data_init(t_table *table)
{
    int i;

   table->end_simulation = false;
   table->all_threads_ready = false;
   table->philos = safe_malloc(sizeof(t_philo) * table->philo_number);
   safe_mutex_handle(&table->table_mutex, INIT);
   table->forks = safe_malloc(sizeof(t_fork) * table->philo_number);
   i = 0;
   while (i < table->philo_number)
   {
        safe_mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
        i++;
   }
   philo_init(table);

}