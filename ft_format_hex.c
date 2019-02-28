/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 20:35:33 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/28 20:49:20 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static size_t	format_hex_prepare_mem(t_specification spec, char *str)
{
	size_t	res;

	ft_memset(str, ' ', spec.minwidth);
	if (spec.force_zeroes && spec.align_left)
		ft_memset(str, '0', spec.precision);
	else if (spec.force_zeroes && !spec.precision_set)
		ft_memset(str, '0', spec.minwidth);
	else if (spec.force_zeroes && spec.precision != 0)
		ft_memset(str + spec.minwidth - spec.precision, '0', spec.precision);
	if (spec.align_left || (spec.force_zeroes && !spec.precision_set))
		res = 0;
	else
		res = spec.minwidth - spec.precision;
	return (res);
}

void			ft_format_hex(unsigned long long int nbr,
								t_specification spec,
								char *str, char b)
{
	size_t			i;
	size_t			digits;

	i = format_hex_prepare_mem(spec, str);
	digits = spec.align_left ? spec.precision : spec.minwidth;
	while (digits != i)
	{
		digits--;
		str[digits] = (nbr & 0xF) + '0';
		if (str[digits] > '9')
			str[digits] = str[digits] - '0' - 10 + b;
		nbr /= 16;
	}
	if (spec.alt_print)
	{
		if (spec.align_left)
			digits = 0;
		str[digits] = '0';
		str[digits + 1] = b >= 'a' && b <= 'z' ? 'x' : 'X';
	}
}
