/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:17:31 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/22 17:41:51 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "libftprintf.h"

int		ft_printf(const char *format, ...)
{
	t_smartstr	buffer;
	ssize_t		bytes;
	va_list		ap;

	va_start(ap, format);
	// checks format for null etc
	buffer.str = NULL;
	buffer.size = 0;
	buffer.len = 0;
	while (*format != '\0')
	{
		// fill buffer
		// check buffer not empty
	}
	bytes = write(1, buffer.str, buffer.len);
	va_end(ap);
	return (bytes);
}
