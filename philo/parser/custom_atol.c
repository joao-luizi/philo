/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_atol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:17:41 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/24 14:24:24 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Checks if a character is a whitespace character.
 *
 * @param c The character to check.
 * @return true if the character is a whitespace, false otherwise.
 */
static bool	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

/**
 * @brief Checks if a character is a signal ('-' or '+').
 *
 * @param c The character to check.
 * @return true if the character is a signal, false otherwise.
 */
static bool	is_signal(char c)
{
	return (c == '-' || c == '+');
}

/**
 * @brief Checks if a character is a digit.
 *
 * @param c The character to check.
 * @return true if the character is a digit, false otherwise.
 */
static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Validates the input string to ensure it represents a valid
 * positive number.
 *
 * This function skips leading whitespace characters, checks for a signal,
 *  and ensures
 * the input contains only digits. If the input is invalid, it sets the error
 *  flag and
 * prints an appropriate error message.
 *
 * @param str The input string to validate.
 * @param error Pointer to a boolean flag that indicates if an error occurred.
 * @return A pointer to the first valid character in the input string, or the
 *  original
 *         string if an error occurred.
 */
static const char	*valid_input(const char *str, bool *error)
{
	while (*str && is_space(*str))
		str++;
	while (*str && is_signal(*str))
	{
		if (*str == '-')
		{
			*error = true;
			ft_putstr_fd(R "Invalid Input: Only positive numbers allowed\n" RST,
				STDERR_FILENO);
			return (str);
		}
		else
			str++;
	}
	if (!is_digit(*str))
	{
		*error = true;
		ft_putstr_fd(R "Invalid Input: Only numbers allowed\n" RST,
			STDERR_FILENO);
		return (str);
	}
	return (str);
}

/**
 * @brief Converts a string to a long integer, ensuring the input is
 * valid and within range.
 *
 * This function validates the input string to ensure it represents a
 * positive number.
 * It then converts the string to a long integer. If the number exceeds
 * INT_MAX or the
 * input is invalid, it sets the error flag and returns 0.
 *
 * @param str The input string to convert.
 * @param error Pointer to a boolean flag that indicates if an error
 * occurred.
 * @return The converted long integer, or 0 if an error occurred.
 */
unsigned int	custom_atol(const char *str, bool *error)
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
			ft_putstr_fd(R "Invalid Input: INT_MAX is the \
				maximun allowed\n" RST, STDERR_FILENO);
			return (0);
		}
		str++;
	}
	return (num);
}
