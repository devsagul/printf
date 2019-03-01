/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 22:17:08 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/01 11:42:43 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"

static int				utf8_strlen(unsigned int *str, int max)
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

unsigned int			*get_null_utf8_str(void)
{
	unsigned int	*res;

	res = (unsigned int *)malloc(sizeof(unsigned int) * 7);
	if (res == NULL)
		return (NULL);
	res[0] = '(';
	res[1] = 'n';
	res[2] = 'u';
	res[3] = 'l';
	res[4] = 'l';
	res[5] = ')';
	res[6] = '\0';
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

size_t					ft_unicode_format(char **pdst, t_specification spec,
											va_list ap)
{
	int				len;
	char			*str;
	unsigned int	*arg;

	arg = (unsigned int *)va_arg(ap, unsigned int *);
	if (arg == NULL)
		arg = get_null_utf8_str();
	if (arg == NULL)
		return (0);
	if (spec.precision_set)
		len = utf8_strlen(arg, spec.precision);
	else
		len = utf8_strlen(arg, 1000);
	if (!spec.precision_set)
		spec.precision = len;
	if (len < spec.precision)
		spec.precision = len;
	if (spec.minwidth < spec.precision)
		spec.minwidth = spec.precision;
	str = (char *)malloc(sizeof(char) * (spec.minwidth + 4));
	if (str == NULL)
		return (0);
	if (!spec.force_zeroes || spec.align_left)
		ft_memset(str, ' ', sizeof(char) * spec.minwidth);
	else
		ft_memset(str, '0', sizeof(char) * spec.minwidth);
	str[spec.minwidth] = '\0';
	str[spec.minwidth + 1] = '\0';
	str[spec.minwidth + 2] = '\0';
	str[spec.minwidth + 3] = '\0';
	if (!spec.align_left)
		spec.minwidth += utf8_strncpy(str + spec.minwidth - spec.precision, arg, spec.precision);
	else
		spec.minwidth += utf8_strncpy(str, arg, spec.precision);
	*pdst = str;
	return (spec.minwidth);
}
