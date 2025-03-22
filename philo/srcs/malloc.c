/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcameira <jcameira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 11:38:10 by jcameira          #+#    #+#             */
/*   Updated: 2024/03/09 16:13:50 by jcameira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdlib.h>

extern void	*__real_malloc(size_t size);

void	*__wrap_malloc(size_t size)
{
	srand(time(NULL));
	if (rand() % 2)
		return (NULL);
	return (__real_malloc(size));
}
