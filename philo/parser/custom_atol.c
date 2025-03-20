/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_atol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:17:41 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/20 00:18:05 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

static bool	is_signal(char c)
{
	return (c == '-' || c == '+');
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_input(const char *str, bool *error)
{
	while (*str && is_space(*str))
		str++;
	while (*str && is_signal(*str))
	{
		if (*str == '-')
		{
			*error = true;
			printf(R "Invalid Input: Only positive numbers allowed\n" RST);
			return (str);
		}
		else
			str++;
	}
	if (!is_digit(*str))
	{
		*error = true;
		printf(R "Invalid Input: Only numbers allowed\n" RST);
		return (str);
	}
	return (str);
}

long	custom_atol(const char *str, bool *error)
{
	long	num;

	if (*error)
		return (0);
	num = 0;
	str = valid_input(str, error);
	if (*error)
		return (0);
	while (*str && is_digit(*str))
	{
		num = (num * 10) + (*str - '0');
		if (num > INT_MAX)
		{
			*error = true;
			printf(R "Invalid Input: INT_MAX is the maximun allowed\n" RST);
			return (0);
		}
		str++;
	}
	return (num);
}
