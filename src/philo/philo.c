# include "../inc/philo.h"

bool philo_died(t_philo *philo, t_table *table)
{
    long elapsed;
    long time_to_die;


    if (get_bool(&philo->philo_mutex, &philo->full))
        return (false);
    elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
    time_to_die = table->time_to_die / 1000;

    if (elapsed > time_to_die)
        return (true);
    return (false);


}

void philo_think(t_philo *philo)
{
    write_status(THINKING, philo);
}

void philo_eat(t_philo *philo)
{
    t_table *table;

    table = get_table(NULL);
    safe_mutex_handle(&philo->first_fork->fork, LOCK);
    write_status(TAKE_FIRST_FORK, philo);
    safe_mutex_handle(&philo->second_fork->fork, LOCK);
    write_status(TAKE_SECOND_FORK, philo);
    set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(MILLISECOND));
    philo->meal_counter++;
    write_status(EATING,philo);
    custom_usleep(table->time_to_eat, table);
    if (table->nbr_limit_meals > 0 && philo->meal_counter == table->nbr_limit_meals)
        set_bool(&philo->philo_mutex, &philo->full, true);
    safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
    safe_mutex_handle(&philo->second_fork->fork, UNLOCK);

}

static void assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
    int philo_number;

    philo_number = philo->table->philo_number;
    philo->first_fork= &forks[(philo_pos + 1) % philo_number];
    philo->second_fork = &forks[philo_pos];
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &forks[philo_pos];
        philo->second_fork= &forks[(philo_pos + 1) % philo_number];
    }
    
}

void philo_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = 0;
    while (i <table->philo_number)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meal_counter = 0;
        philo->table = table;
        safe_mutex_handle(&philo->philo_mutex, INIT);
        assign_forks(philo, table->forks, i);
        i++;
    }
}