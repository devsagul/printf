/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getspecificator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 17:33:46 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/24 19:45:11 by mbalon-s         ###   ########.fr       */
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
	else if (*format == 'd' || *format == 'i')
		pspec->specificator = INTEGER;
	else if (*format == 'o')
		pspec->specificator = OCT;
	else
	{
		pspec->specificator = UNKNOWN;
		return (0);
	}
	return (res);
}
