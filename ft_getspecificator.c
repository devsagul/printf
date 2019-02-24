/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getspecificator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 17:33:46 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/24 20:41:54 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>

size_t				ft_getspecificator(const char *format,
										t_specification *pspec)
{
	size_t	res;

	res = 1;
	if (*format == '%')
		pspec->specificator = PERCENT;
	else if (*format == 'c')
		pspec->specificator = CHAR;
	else if (*format == 's')
		pspec->specificator = STRING;
	else if (*format == 'd' || *format == 'i' || *format == 'D')
		pspec->specificator = INTEGER;
	else if (*format == 'o' || *format == 'O')
		pspec->specificator = OCT;
	else if (*format == 'x')
		pspec->specificator = HEX;
	else if (*format == 'X')
		pspec->specificator = HEX_UPPER;
	else
	{
		pspec->specificator = UNKNOWN;
		return (0);
	}
	return (res);
}
