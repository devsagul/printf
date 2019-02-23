/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:20:21 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/23 17:17:01 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

size_t	ft_percent_format(char **pdst, t_specification spec)
{
	size_t	res;

	res = spec.minwidth;
	if (res <= 0)
		res = 1;
	*pdst = (char *) malloc(sizeof(char) * (res + 1));
	if (*pdst == NULL)
		return (0);
	ft_memset(*pdst, ' ', sizeof(char) * res);
	*pdst[res] = '\0';
	if (spec.align_left)
		*pdst[0] = '%';
	else
		*pdst[res] = '%';
	return (res);
}
