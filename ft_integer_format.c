/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 22:41:32 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/01 20:22:13 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

static void			format_integer_prepare_memory(t_specification spec,
													char *str)
{
	ft_memset(str, ' ', spec.minwidth);
	if (spec.force_zeroes && spec.align_left)
		ft_memset(str, '0', spec.precision);
	else if (spec.force_zeroes && !spec.precision_set)
		ft_memset(str, '0', spec.minwidth);
	else if (spec.force_zeroes && spec.precision != 0)
		ft_memset(str + spec.minwidth - spec.precision, '0', spec.precision);
}

static size_t		format_integer_get_initial_position(t_specification spec)
{
	if (spec.align_left || (spec.force_zeroes && !spec.precision_set))
		return (0);
	return (spec.minwidth - spec.precision);
}

static void			format_integer(long long int nbr, t_specification spec,
									char *str)
{
	size_t			i;
	size_t			digits;

	format_integer_prepare_memory(spec, str);
	i = format_integer_get_initial_position(spec);
	digits = spec.align_left ? spec.precision : spec.minwidth;
	if (spec.force_sign && nbr >= 0)
		str[i++] = '+';
	else if (spec.force_spacing && nbr >= 0)
		str[i++] = ' ';
	else if (nbr < 0)
	{
		if (-nbr == nbr)
		{
			str[--digits] = '0' - nbr % 10;
			nbr /= 10;
		}
		nbr *= -1;
		str[i++] = '-';
	}
	while (digits != i)
	{
		str[--digits] = nbr % 10 + '0';
		nbr /= 10;
	}
}

size_t				ft_integer_format(char **pdst, t_specification spec,
										va_list ap)
{
	long long int	nbr;
	int				num_digits;
	char			*str;

	nbr = ft_get_signed_arg(ap, spec);
	num_digits = ft_count_digits_signed(nbr);
	if (nbr == 0 && ((spec.precision_set && spec.precision) ||
						!spec.precision_set))
		num_digits++;
	if (nbr < 0 || spec.force_sign || ((spec.force_spacing)))
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
