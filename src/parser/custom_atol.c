# include "../inc/philo.h"

static bool is_space(char c)
{
    return (c == 32 || (c >= 9 && c <= 13));
}

static bool is_signal(char c)
{
    return (c == '-' || c == '+');
}

static bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}
static const char *valid_input(const char *str)
{
    while (*str && is_space(*str))
        str++;
    while (*str && is_signal(*str))
    {
        if (*str == '-')
            error_exit("Only positive numbers allowed\n", "custom_atol @ parser/custom_atol.c");
        else
            str++;
    }
    if (!is_digit(*str))
        error_exit("Invalid character found\n", "custom_atol @ parser/custom_atol.c");
    return (str);
}
long custom_atol(const char *str)
{
    long num;
    
    num = 0;
    str = valid_input(str);
    while (*str && is_digit(*str))
    {
        num = (num * 10) + (*str - '0');
        if (num > INT_MAX)
            error_exit("Invalid Input: INT_MAX is the maximun allowed\n", "custom_atol @ parser/custom_atol.c");
        str++;
    }
    return (num);
}
