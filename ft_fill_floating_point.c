/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_floating_point.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 20:00:26 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/02 14:21:30 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void					ft_fill_floating_point(double nbr,
												t_floating_point *dst)
{
	unsigned long int	byte_repr;

	byte_repr = *((unsigned long *)&nbr);
	dst->sign = byte_repr & 0x8000000000000000;
	dst->exponent = ((byte_repr >> 52) & 0x7FF) - 1023;
	dst->fraction = byte_repr & 0xFFFFFFFFFFFFF;
	if (dst->exponent == -1023 && dst->fraction != 0)
	{
		while (!(dst->fraction & 0x8000000000000))
		{
			dst->fraction <<= 1;
			dst->exponent--;
		}
		dst->fraction <<= 1;
		dst->fraction &= 0xFFFFFFFFFFFFFFFF;
	}
}
