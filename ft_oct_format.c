/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oct_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 19:42:55 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/28 21:06:33 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

static void			format_oct(unsigned long long int nbr,
									t_specification spec,
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
	while (digits != i)
	{
		digits--;
		str[digits] = (nbr & 0x7) + '0';
		nbr /= 8;
	}
}

size_t				ft_oct_format(char **pdst, t_specification spec,
										va_list ap)
{
	unsigned long long int	nbr;
	int						num_digits;
	char					*str;

	nbr = ft_get_unsigned_arg(ap, spec);
	num_digits = ft_count_digits_unsigned(nbr, 8);
	if (spec.alt_print && nbr != 0)
		num_digits++;
	if (nbr == 0 && ((spec.precision_set && spec.precision != 0) ||
						!spec.precision_set || spec.alt_print))
		num_digits++;
	if (!spec.precision_set || spec.precision < num_digits)
		spec.precision = num_digits;
	if (spec.minwidth < spec.precision)
		spec.minwidth = spec.precision;
	str = (char *)malloc(sizeof(char) * spec.minwidth + 1);
	if (str == NULL)
		return (0);
	str[spec.minwidth] = '\0';
	format_oct(nbr, spec, str);
	*pdst = str;
	return (spec.minwidth);
}
