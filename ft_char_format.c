/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:58:19 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/28 19:24:41 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"

static int			utf8_count_bytes(unsigned int c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x10FFFF)
		return (4);
	return (0);
}

static unsigned int	utf8_convert(unsigned int c, int bytes)
{
	unsigned int	res;

	res = c;
	if (bytes == 1)
		res = c & 0x7F;
	else if (bytes == 2)
		res = 0xC000 | ((c & 0x7C0) << 2) | 0x80 | (c & 0x3F);
	else if (bytes == 3)
	{
		res = 0xE00000 | ((c & 0xF000) << 4) | 0x8000;
		res |= ((c & 0xFC0) << 2) | 0x80 | (c & 0x3F);
	}
	else if (bytes == 4)
	{
		res = 0xF0000000 | (c & 0x0E0000) | 0x800000;
		res |= ((c & 0x3F000) << 4) | 0x8000;
		res |= ((c & 0xFC0) << 2) | 0x80 | (c & 0x3F);
	}
	return (res);
}

static size_t		unicode_char_format(char **pdst, t_specification spec,
										va_list ap)
{
	size_t			res;
	int				bytes;
	char			*str;
	unsigned int	c;
	int				i;

	c = va_arg(ap, unsigned int);
	bytes = utf8_count_bytes(c);
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
	c = utf8_convert(c, bytes);
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
	unsigned int	c;
	int				i;

	if (spec.long_long_mod || spec.long_mod)
		return (unicode_char_format(pdst, spec, ap));
	c = va_arg(ap, unsigned int);
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
	if (spec.precision_set && spec.precision < 1)
		return (res);
	i = spec.align_left ? 0 : res - 1;
	str[i] = c;
	return (res);
}
