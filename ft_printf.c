/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:17:31 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/24 22:07:06 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

static size_t	get_mods(const char *format, t_specification *pspec)
{
	const char	*s;

	s = format;
	while (ft_instr(*s, "-+ 0#hlLzj"))
	{
		if (*s == '-')
			pspec->align_left = 1;
		else if (*s == '+')
			pspec->force_sign = 1;
		else if (*s == ' ')
			pspec->force_spacing = 1;
		else if (*s == '0')
			pspec->force_zeroes = 1;
		else if (*s == '#')
			pspec->alt_print = 1;
		else if (*s == 'h')
		{
			if (pspec->short_mod)
				pspec->short_short_mod = 1;
			else
				pspec->short_mod = 1;
		}
		else if (*s == 'l')
		{
			if (pspec->long_mod)
				pspec->long_long_mod = 1;
			else
				pspec->long_mod = 1;
		}
		else if (*s == 'L')
			pspec->long_double_mod = 1;
		else if (*s == 'z')
			pspec->size_t_mod = 1;
		else if (*s == 'j')
			pspec->intmax_t_mod = 1;
		s++;
	}
	return (s - format);
}

static size_t	get_specification(const char *format,
									t_specification *pspec)
{
	const char		*s;
	unsigned long	tmp;

	s = format;
	s += get_mods(s, pspec);
	if (*s >= '1' && *s <= '9')
	{
		s += ft_ulfromstr(s, &tmp);
		pspec->minwidth = tmp;
	}
	else if (*s == '*')
	{
		pspec->wildcard_minwidth = 1;
		s++;
	}
	if (*s == '.')
	{
		s++;
		pspec->precision_set = 1;
		pspec->precision = 0;
		if (*s >= '0' && *s <= '9')
		{
			s += ft_ulfromstr(s, &tmp);
			pspec->precision = tmp;
		}
		else if (*s == '*')
		{
			pspec->wildcard_precision = 1;
			s++;
		}
	}
	while (ft_instr(*s, ".0123456789"))
		s++;
	s += get_mods(s, pspec);
	s += ft_getspecificator(s, pspec);
	return (s - format);
}

static size_t	progress_buffer(const char *format,
								t_smartstr *pbuf, va_list ap)
{
	char			*s;
	t_specification	spec;
	size_t			res;

	if (*format != '%')
	{
		s = ft_strchr(format, '%');
		if (s == NULL)
			s = ft_strchr(format, '\0');
		ft_smartstrncat(pbuf, format, s - format);
		return (s - format);
	}
	format++;
	res = 1;
	ft_bzero(&spec, sizeof(spec));
	res += get_specification(format, &spec);
	if (spec.wildcard_minwidth)
		spec.minwidth = va_arg(ap, int);
	if (spec.wildcard_precision)
		spec.precision = va_arg(ap, int);
	ft_getstrbyspec(spec, pbuf, ap);
	return (res);
}

int				ft_printf(const char *format, ...)
{
	t_smartstr	buffer;
	ssize_t		bytes;
	va_list		ap;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	ft_bzero(&buffer, sizeof(buffer));
	while (*format != '\0')
		format += progress_buffer(format, &buffer, ap);
	va_end(ap);
	bytes = write(1, buffer.str, buffer.len);
	ft_flushsmartstr(&buffer);
	return (bytes);
}
