# ifndef DEFINES_H
#define DEFINES_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>
# include <errno.h>

# define DEBUG true
//default color
# define RST "\033[0m" 
//RED Color (Bold)
# define R   "\033[1;31m" 
//GREEN Color (Bold)
# define G   "\033[1;32m"
//YELLOW Color (Bold)
# define Y   "\033[1;33m" 
//BLUE Color (Bold)
# define B   "\033[1;34m" 
//MAGENTA Color (Bold)
# define M   "\033[1;35m"
//CYAN Color (Bold)
# define C   "\033[1;36m"
//WHITE Color (Bold)
# define W   "\033[1;37m"

typedef enum e_opcode
{
    LOCK,
    UNLOCK, 
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH
}t_opcode;

typedef enum e_time_code
{
    SECOND, 
    MILLISECOND,
    MICROSECOND,

} t_time_code;

#endif