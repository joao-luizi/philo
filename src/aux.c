# include "../inc/philo.h"
void *safe_malloc(size_t bytes)
{
    void *ret;

    ret = malloc(bytes);
    if (!ret)
        error_exit(R "Error on memory allocation" RST);
    memset(ret,0,bytes);
    return (ret);
}

void error_exit(const char *error)
{
    printf(R "%s\n" RST, error);
    exit(EXIT_FAILURE);
}
