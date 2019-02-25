/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:17:46 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/25 21:41:15 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

static int			count_digits(unsigned long long int nbr)
{
	int		res;

	res = 0;
	while (nbr != 0)
	{
		nbr /= 16;
		res++;
	}
	return (res);
}

static void			format_integer(unsigned long long int nbr, t_specification spec,
									char *str)
{
	size_t			i;
	size_t			digits;

	ft_memset(str, ' ', sizeof(char) * spec.minwidth);
	if (spec.align_left)
		i = 0;
	else
		i = spec.minwidth - spec.precision;
	if (!spec.align_left)
		digits = spec.minwidth;
	else
		digits = spec.precision;
	while (digits != i)
	{
		digits--;
		str[digits] = (nbr & 0xF) + '0';
		if (str[digits] > '9')
			str[digits] = str[digits] - '0' - 10 + 'a';
		nbr >>= 4;
	}
	if (!spec.align_left && !spec.force_zeroes)
	{
		str[digits] = '0';
		str[digits + 1] = 'x';
	}
	else
	{
		str[0] = '0';
		str[1] = 'x';
	}
}

size_t				ft_pointer_format(char **pdst, t_specification spec,
										va_list ap)
{
	unsigned long long int	nbr;
	int						num_digits;
	char					*str;

	nbr = (unsigned long long) va_arg(ap, void *);
	num_digits = count_digits(nbr);
	if (nbr == 0)
	{
		if (spec.precision_set && spec.precision == 0)
			spec.precision = 2;
		else if (!spec.precision_set || spec.precision < 3)
			spec.precision = 3;
		else
			spec.precision += 2;
	}
	else if (!spec.precision_set || spec.precision < num_digits + 2)
		spec.precision = num_digits + 2;
	else
		spec.precision += 2;
	if (spec.minwidth < spec.precision)
		spec.minwidth = spec.precision;
	str = (char *)malloc(sizeof(char) * spec.minwidth + 1);
	if (str == NULL)
		return (0);
	str[spec.minwidth] = '\0';
	format_integer(nbr, spec, str);
	*pdst = str;
	return (spec.minwidth);
}
