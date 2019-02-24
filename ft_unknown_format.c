/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unknown_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 23:36:50 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/24 23:40:31 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"

size_t				ft_unknown_format(char **pdst, t_specification spec)
{
	int		len;
	char	*str;

	len = 0;
	spec.minwidth--;
	if (!spec.precision_set)
		spec.precision = len;
	if (len < spec.precision)
		spec.precision = len;
	if (spec.minwidth < len)
		spec.minwidth = spec.precision;
	str = (char *)malloc(sizeof(char) * (spec.minwidth + 1));
	if (str == NULL)
		return (0);
	if (!spec.force_zeroes || spec.align_left)
		ft_memset(str, ' ', sizeof(char) * spec.minwidth);
	else
		ft_memset(str, '0', sizeof(char) * spec.minwidth);
	str[spec.minwidth] = '\0';
	*pdst = str;
	return (spec.minwidth);
}
