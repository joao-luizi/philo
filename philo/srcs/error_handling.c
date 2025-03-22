/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:49:12 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/14 21:16:13 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	argument_number_error(void)
{
	printf(ARG_NBR_ERROR);
	return (1);
}

int	inv_argument_error(void)
{
	printf(INV_ARG_ERROR);
	return (1);
}
