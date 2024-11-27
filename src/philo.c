# include "../inc/philo.h"



int main(int argc, char **argv)
{
    (void)argv;
    t_table table;
    if (argc == 5 || argc == 6)
    {
        parse_input(&table, argv);
        printf("Simulation starting with P: %ld TTD: %ld TTS %ld TTE %ld (Meals: %ld)\n",
         table.philo_number, table.time_to_die, table.time_to_sleep, table.time_to_eat, table.nbr_limit_meals);
        data_init(&table);
    }
    else
        error_exit("Wrong input\n"\
            G"Example usage: ./philo (number of philosophers) \
(time to die) (time to eat) (time to sleep) [number of meals]\n\
./philo 5 800 200 200\n\
() - required [] - optional"RST);
    return (0);
}