/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 19:59:02 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/28 20:35:30 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

size_t				ft_hex_format(char **pdst, t_specification spec,
										va_list ap)
{
	unsigned long long int	nbr;
	int						num_digits;
	char					*str;

	nbr = ft_get_unsigned_arg(ap, spec);
	spec.alt_print = nbr == 0 ? 0 : spec.alt_print;
	num_digits = ft_count_digits_unsigned(nbr, 16);
	num_digits += spec.alt_print && nbr != 0 ? 2 : 0;
	spec.precision += spec.alt_print && nbr != 0 ? 2 : 0;
	if (nbr == 0 && ((spec.precision_set && spec.precision != 0)
		|| !spec.precision_set))
		num_digits++;
	if (!spec.precision_set || spec.precision < num_digits)
		spec.precision = num_digits;
	if (spec.minwidth < spec.precision)
		spec.minwidth = spec.precision;
	str = (char *)malloc(sizeof(char) * spec.minwidth + 1);
	if (str == NULL)
		return (0);
	str[spec.minwidth] = '\0';
	ft_format_hex(nbr, spec, str, 'a');
	*pdst = str;
	return (spec.minwidth);
}
