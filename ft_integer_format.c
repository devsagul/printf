/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 22:41:32 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/25 23:14:06 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

static int			count_digits(long long int nbr)
{
	int		res;

	res = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		res++;
	}
	return (res);
}

static void			format_integer(long long int nbr, t_specification spec,
									char *str)
{
	size_t			i;
	size_t			digits;

	ft_memset(str, ' ', spec.minwidth);
	if (spec.force_zeroes && spec.align_left)
		ft_memset(str, '0', spec.precision);
	else if (spec.force_zeroes && !spec.precision_set)
		ft_memset(str, '0', spec.minwidth);
	else if (spec.force_zeroes && spec.precision != 0)
		ft_memset(str + spec.minwidth - spec.precision, '0', spec.precision);
	if (spec.align_left || (spec.force_sign && spec.force_zeroes))
		i = 0;
	else
		i = spec.minwidth - spec.precision;
	if (!spec.align_left)
		digits = spec.minwidth;
	else
		digits = spec.precision;
	if (spec.force_sign && nbr >= 0)
		str[i++] = '+';
	else if (spec.force_spacing && nbr >= 0)
		str[i++] = ' ';
	else if (nbr < 0)
	{
		if (-nbr == nbr)
		{
			digits--;
			str[digits] = '0' - nbr % 10;
			nbr /= 10;
		}
		nbr *= -1;
		str[i++] = '-';
	}
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
	long long int	nbr;
	int				num_digits;
	char			*str;

	if (spec.long_long_mod)
		nbr = va_arg(ap, long long int);
	else if	(spec.intmax_t_mod)
		nbr = (intmax_t) va_arg(ap, intmax_t);
	else if	(spec.size_t_mod)
		nbr = (ssize_t) va_arg(ap, ssize_t);
	else if (spec.long_mod)
		nbr = va_arg(ap, long int);
	else if (spec.short_short_mod)
		nbr = (char) va_arg(ap, int);
	else if (spec.short_mod)
		nbr = (short int) (unsigned int) va_arg(ap, int);
	else
		nbr = va_arg(ap, int);
	num_digits = count_digits(nbr);
	if (nbr == 0 && ((spec.precision_set && spec.precision != 0) || !spec.precision_set))
	{
		num_digits++;
		if (spec.force_zeroes && !spec.align_left)
			num_digits++;
	}
	if (nbr < 0)
		spec.force_sign = 1;
	if (nbr < 0 || spec.force_sign || spec.force_spacing)
	{
		num_digits++;
		spec.precision++;
	}
	if (!spec.precision_set || spec.precision < num_digits)
		spec.precision = num_digits;
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
