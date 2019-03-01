/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unknown_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 23:36:50 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/01 11:45:28 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"

size_t				ft_unknown_format(char **pdst, t_specification spec)
{
	char	*str;

	if (spec.ch == '\0')
	{
		*pdst = NULL;
		return (0);
	}
	if (!spec.precision_set || 1 < spec.precision)
		spec.precision = 1;
	spec.minwidth = spec.minwidth < 1 ? spec.precision : spec.minwidth;
	str = (char *)malloc(sizeof(char) * (spec.minwidth + 1));
	if (str == NULL)
		return (0);
	if (!spec.force_zeroes || spec.align_left)
		ft_memset(str, ' ', sizeof(char) * spec.minwidth);
	else
		ft_memset(str, '0', sizeof(char) * spec.minwidth);
	str[spec.minwidth] = '\0';
	if (spec.align_left)
		str[0] = spec.ch;
	else
		str[spec.minwidth - 1] = spec.ch;
	*pdst = str;
	return (spec.minwidth);
}
