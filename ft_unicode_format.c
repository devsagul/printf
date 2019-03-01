/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 22:17:08 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/01 11:59:44 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"

static int				utf8_strlen_limited(unsigned int *str, int max)
{
	int		res;

	res = 0;
	while (*str != '\0')
	{
		res += ft_utf8_count_bytes(*str);
		if (res > max)
		{
			res -= ft_utf8_count_bytes(*str);
			return (res);
		}
		str++;
	}
	return (res);
}

static int				utf8_strlen(unsigned int *str)
{
	int		res;

	res = 0;
	while (*str != '\0')
	{
		res += ft_utf8_count_bytes(*str);
		str++;
	}
	return (res);
}

int						utf8_strncpy(char *dst, unsigned int *src, int length)
{
	size_t			i;
	size_t			j;
	unsigned int	c;
	int				bytes;
	int				res;

	i = 0;
	j = 0;
	res = 0;
	while (src[j] != '\0' && ft_utf8_count_bytes(src[j]) + res <= length)
	{
		bytes = ft_utf8_count_bytes(src[j]);
		c = ft_utf8_convert(src[j], bytes);
		res += bytes;
		while (bytes)
		{
			bytes--;
			dst[i] = (char)(((0xFF << 8 * bytes) & c) >> 8 * bytes);
			i++;
		}
		j++;
	}
	return (0);
}

t_specification			unicode_format_prepare(unsigned int *arg,
												t_specification spec)
{
	int				len;

	if (spec.precision_set)
		len = utf8_strlen_limited(arg, spec.precision);
	else
		len = utf8_strlen(arg);
	if (!spec.precision_set || len < spec.precision)
		spec.precision = len;
	if (spec.minwidth < spec.precision)
		spec.minwidth = spec.precision;
	return (spec);
}

size_t					ft_unicode_format(char **pdst, t_specification spec,
											va_list ap)
{
	char			*str;
	unsigned int	*arg;

	arg = (unsigned int *)va_arg(ap, unsigned int *);
	if (arg == NULL)
		arg = (unsigned int *)L"(null)";
	spec = unicode_format_prepare(arg, spec);
	str = (char *)malloc(sizeof(char) * (spec.minwidth + 4));
	if (str == NULL)
		return (0);
	if (!spec.force_zeroes || spec.align_left)
		ft_memset(str, ' ', sizeof(char) * spec.minwidth);
	else
		ft_memset(str, '0', sizeof(char) * spec.minwidth);
	ft_bzero(str + spec.minwidth, 4);
	if (!spec.align_left)
		spec.minwidth += utf8_strncpy(str + spec.minwidth - spec.precision,
										arg, spec.precision);
	else
		spec.minwidth += utf8_strncpy(str, arg, spec.precision);
	*pdst = str;
	return (spec.minwidth);
}
