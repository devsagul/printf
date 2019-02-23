/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 22:41:32 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/23 23:49:37 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

static int			count_digits(long long int nbr)
{
	size_t			res;

	res = 0;
	while (nbr)
	{
		nbr *= 0.1;
		res++;
	}
	return (res);
}

static void			format_integer(long long int nbr, t_specification spec,
									char *str, int num_digits)
{
	size_t			i;
	size_t			digits;

	if (spec.force_zeroes)
		ft_memset(str, '0', sizeof(char) * spec.minwidth);
	else
		ft_memset(str, ' ', sizeof(char) * spec.minwidth);
	if (spec.align_left || spec.force_zeroes)
		i = ;
	else
		i = spec.minwidth - num_digits;
	if (spec.force_sign && nbr >= 0)
		str[i++] = '+';
	else if (spec.force_spacing && nbr >= 0)
		str[i++] = ' ';
	else if (nbr < 0)
	{
		nbr *= -1;
		str[i++] = '-';
	}
	digits = spec.precision;
	if (nbr == 0)
		str[digits - 1] = '0';
	while (digits != i)
	{
		digits--;
		str[digits] = nbr % 10 + '0';
		nbr /= 10;
	}
}

size_t				ft_integer_format(char **pdst, t_specification spec,
										va_list ap)
{
	long long	nbr;
	int			num_digits;
	char		*str;

	if (spec.long_long_mod)
		nbr = va_arg(ap, long long int);
	if (spec.long_mod)
		nbr = va_arg(ap, long int);
	if (spec.short_mod)
		nbr = (short int) va_arg(ap, int);
	if (spec.short_short_mod)
		nbr = (short int) va_arg(ap, int);
	else
		nbr = va_arg(ap, int);
	num_digits = count_digits(nbr);
	if (nbr < 0 || spec.force_sign || spec.force_spacing)
		num_digits++;
	if (!spec.precision_set)
		spec.precision = num_digits;
	if (num_digits < spec.precision)
		spec.precision = num_digits;
	if (spec.minwidth < num_digits)
		spec.minwidth = spec.precision;
	str = (char *)malloc(sizeof(char) * spec.minwidth + 1);
	if (str == NULL)
		return (0);
	str[spec.minwidth] = '\0';
	format_integer(nbr, spec, str, num_digits);
	*pdst = str;
	return (spec.minwidth);
}
