/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getspecificator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 17:33:46 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/02 22:01:24 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>

static size_t		additional_getspecificator(const char *format,
										t_specification *pspec)
{
	size_t	res;

	res = 1;
	if (*format == '%')
		pspec->specificator = PERCENT;
	else if (*format == 'p')
		pspec->specificator = POINTER;
	else if (*format == 'a')
		pspec->specificator = A_FLOAT;
	else if (*format == 'A')
		pspec->specificator = A_FLOAT_UPPER;
	else if (*format == 'f')
		pspec->specificator = FLOAT;
	else
	{
		pspec->specificator = UNKNOWN;
		pspec->ch = *format;
		return (*format == '\0' ? 0 : 1);
	}
	return (res);
}

size_t				ft_getspecificator(const char *format,
										t_specification *pspec)
{
	size_t	res;

	res = 1;
	if (*format == 'c' || *format == 'C')
		pspec->specificator = CHAR;
	else if (*format == 's' || *format == 'S')
		pspec->specificator = STRING;
	else if (*format == 'd' || *format == 'i' || *format == 'D')
		pspec->specificator = INTEGER;
	else if (*format == 'o' || *format == 'O')
		pspec->specificator = OCT;
	else if (*format == 'x')
		pspec->specificator = HEX;
	else if (*format == 'X')
		pspec->specificator = HEX_UPPER;
	else if (*format == 'u' || *format == 'U')
		pspec->specificator = UNSIGNED;
	else
		return (additional_getspecificator(format, pspec));
	if (*format == 'D' || *format == 'O' ||
		*format == 'U' || *format == 'C' || *format == 'S')
		pspec->long_long_mod = 1;
	return (res);
}
