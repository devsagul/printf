/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_long_floating_point.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:53:53 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/02 14:45:59 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void					ft_fill_long_floating_point(long double nbr,
												t_floating_point *dst)
{
	unsigned long int	byte_repr1;
	unsigned long int	byte_repr2;

	byte_repr1 = *((unsigned long *)&nbr);
	byte_repr2 = *(&byte_repr1 + 1);
	ft_printf("%.8x\n", byte_repr1);
	ft_printf("%.8x\n", byte_repr2);
	dst->sign = byte_repr1 & 0x8000000000000000;
	dst->exponent = ((byte_repr1 >> 52) & 0x7FF) - 16382;
	dst->fraction = byte_repr1 & 0xFFFFFFFFFFFFFFFF;
	if (dst->exponent == -1023 && dst->fraction == 0)
		dst->exponent = 0;
	else if (dst->exponent == -1023)
	{
		while (!(dst->fraction & 0x8000000000000))
		{
			dst->fraction <<= 1;
			dst->exponent--;
		}
	}
}
