/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:58:19 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/23 19:19:27 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"

size_t				ft_char_format(char **pdst, t_specification spec,
									va_list ap)
{
	size_t	res;
	char	*str;
	char	c;

	res = spec.minwidth;
	if (res <= 0)
		res = 1;
	str = (char *)malloc(sizeof(char) * (res + 1));
	if (str == NULL)
		return (0);
	c = (char)va_arg(ap, int);
	if (spec.force_zeroes && !spec.align_left)
		ft_memset(str, '0', sizeof(char) * res);
	else
		ft_memset(str, ' ', sizeof(char) * res);
	str[res] = '\0';
	if (spec.align_left)
		str[0] = c;
	else
		str[res - 1] = c;
	*pdst = str;
	return (res);
}
