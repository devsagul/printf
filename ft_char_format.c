/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:58:19 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/01 15:29:35 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"

static size_t		unicode_char_format(char **pdst, t_specification spec,
										va_list ap)
{
	size_t			res;
	int				bytes;
	char			*str;
	unsigned int	c;
	int				i;

	c = va_arg(ap, int);
	bytes = ft_utf8_count_bytes(c);
	res = bytes >= spec.minwidth ? bytes : spec.minwidth;
	str = (char *)malloc(res + 1);
	if (str == NULL)
		return (0);
	ft_memset(str, spec.force_zeroes && spec.align_left ? '0' : ' ', res);
	str[res] = '\0';
	*pdst = str;
	if (bytes == 0)
		return (res);
	i = spec.align_left ? 0 : res - bytes;
	c = ft_utf8_convert(c, bytes);
	while (bytes)
	{
		bytes--;
		str[i++] = (char)(((0xFF << 8 * bytes) & c) >> 8 * bytes);
	}
	return (res);
}

size_t				ft_char_format(char **pdst, t_specification spec,
									va_list ap)
{
	size_t			res;
	char			*str;
	char			c;
	int				i;

	if (spec.long_long_mod || spec.long_mod)
		return (unicode_char_format(pdst, spec, ap));
	c = va_arg(ap, int);
	res = spec.minwidth < 1 ? 1 : spec.minwidth;
	str = (char *)malloc(res + 1);
	if (str == NULL)
		return (0);
	if (spec.force_zeroes && !spec.align_left)
		ft_memset(str, '0', res);
	else
		ft_memset(str, ' ', res);
	str[res] = '\0';
	*pdst = str;
	i = spec.align_left ? 0 : res - 1;
	str[i] = c;
	return (res);
}
