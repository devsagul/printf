/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:17:46 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/28 21:07:17 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

static void			format_pointer(unsigned long long int nbr,
									t_specification spec,
									char *str)
{
	size_t			i;
	size_t			digits;

	ft_memset(str, ' ', sizeof(char) * spec.minwidth);
	i = spec.align_left ? 0 : spec.minwidth - spec.precision;
	digits = spec.align_left ? spec.precision : spec.minwidth;
	while (digits != i)
	{
		digits--;
		str[digits] = (nbr & 0xF) + '0';
		if (str[digits] > '9')
			str[digits] = str[digits] - '0' - 10 + 'a';
		nbr /= 16;
	}
	i = !(spec.align_left || spec.force_zeroes) ? digits : 0;
	str[i] = '0';
	str[i + 1] = 'x';
}

size_t				ft_pointer_format(char **pdst, t_specification spec,
										va_list ap)
{
	unsigned long long int	nbr;
	int						num_digits;
	char					*str;

	nbr = (unsigned long long)va_arg(ap, void *);
	num_digits = ft_count_digits_unsigned(nbr, 16);
	if (nbr == 0)
		if (spec.precision_set && spec.precision == 0)
			spec.precision = 2;
		else
			spec.precision = (!spec.precision_set || spec.precision < 3) ?
					3 : spec.precision + 2;
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
	format_pointer(nbr, spec, str);
	*pdst = str;
	return (spec.minwidth);
}
