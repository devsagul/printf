/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:17:31 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/01 15:25:02 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

static size_t	update_mw_and_prec(const char *format,
												t_specification *pspec)
{
	const char		*s;
	unsigned long	holder;
	int				wildcard;

	s = format;
	wildcard = *s == '*' ? 1 : 0;
	s += wildcard ? 1 : ft_ulfromstr(s, &holder);
	if (pspec->precision_set)
	{
		if (wildcard)
			pspec->get_wildcard_precision = 1;
		else
			pspec->precision = holder;
		pspec->wildcard_precision = wildcard;
	}
	else
	{
		if (wildcard)
			pspec->get_wildcard_minwidth = 1;
		else
			pspec->minwidth = holder;
		pspec->wildcard_minwidth = wildcard;
	}
	return (s - format);
}

static size_t	get_specification(const char *format,
									t_specification *pspec)
{
	const char		*s;

	s = format;
	while (ft_instr(*s, "-+ #hlLzj.0123456789*"))
	{
		pspec->align_left = *s == '-' ? 1 : pspec->align_left;
		pspec->force_sign = *s == '+' ? 1 : pspec->force_sign;
		pspec->force_spacing = *s == ' ' ? 1 : pspec->force_spacing;
		pspec->force_zeroes = *s == '0' && !pspec->precision_set ?
											1 : pspec->force_zeroes;
		pspec->alt_print = *s == '#' ? 1 : pspec->alt_print;
		pspec->short_short_mod = *s == 'h' && s[1] == 'h' ?
											1 : pspec->short_short_mod;
		pspec->short_mod = *s == 'h' ? 1 : pspec->short_mod;
		pspec->long_long_mod = *s == 'l' && s[1] == 'l' ?
											1 : pspec->long_long_mod;
		pspec->long_mod = *s == 'l' ? 1 : pspec->long_mod;
		pspec->long_double_mod = *s == 'L' ? 1 : pspec->long_double_mod;
		pspec->size_t_mod = *s == 'z' ? 1 : pspec->size_t_mod;
		pspec->intmax_t_mod = *s == 'j' ? 1 : pspec->intmax_t_mod;
		pspec->precision_set = *s == '.' ? 1 : pspec->precision_set;
		s += (ft_instr(*s, "0123456789*")) ? update_mw_and_prec(s, pspec) : 1;
	}
	s += ft_getspecificator(s, pspec);
	return (s - format);
}

static void		load_wildcards(t_specification *pspec, va_list ap)
{
	int				tmp;

	if (pspec->get_wildcard_minwidth)
	{
		tmp = (int)va_arg(ap, int);
		if (pspec->wildcard_minwidth)
			pspec->minwidth = tmp;
	}
	if (pspec->get_wildcard_precision)
	{
		tmp = (int)va_arg(ap, int);
		if (pspec->wildcard_precision)
			pspec->precision = tmp;
	}
	if (pspec->minwidth < 0)
	{
		pspec->align_left = 1;
		pspec->minwidth *= -1;
	}
	if (pspec->precision < 0)
		pspec->precision_set = 0;
}

static size_t	progress_buffer(const char *format,
								t_smartstr *pbuf, va_list ap)
{
	const char		*s;
	t_specification	spec;
	t_specification	*pspec;

	if (*format != '%')
	{
		s = ft_strchr(format, '%');
		if (s == NULL)
			s = ft_strchr(format, '\0');
		ft_smartstrncat(pbuf, format, s - format);
		return (s - format);
	}
	s = format + 1;
	pspec = &spec;
	ft_bzero(pspec, sizeof(spec));
	s += get_specification(s, pspec);
	load_wildcards(pspec, ap);
	ft_getstrbyspec(spec, pbuf, ap);
	return (s - format);
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
