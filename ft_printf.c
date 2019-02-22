/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:17:31 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/22 20:45:01 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

static size_t	progress_buffer_va(const char *format,
									t_smartstr *pbuf, va_list ap)
{
	ap = NULL;
	if (*format == '%')
		return (ft_smartstrncat(pbuf, "%", 1));
	return (0);
}

static size_t	progress_buffer(const char *format,
								t_smartstr *pbuf, va_list ap)
{
	char	*s;

	if (*format != '%')
	{
		s = ft_strchr(format, '%');
		if (s == NULL)
			s = ft_strchr(format, '\0');
		return (ft_smartstrncat(pbuf, format, s - format));
	}
	format++;
	return (progress_buffer_va(format, pbuf, ap) + 1);
}

int				ft_printf(const char *format, ...)
{
	t_smartstr	buffer;
	ssize_t		bytes;
	va_list		ap;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	buffer.str = NULL;
	buffer.size = 0;
	buffer.len = 0;
	while (*format != '\0')
	{
		format += progress_buffer(format, &buffer, ap);
		if (buffer.str == NULL)
			return (-1);
	}
	bytes = write(1, buffer.str, buffer.len);
	va_end(ap);
	ft_flushsmartstr(&buffer);
	return (bytes);
}
