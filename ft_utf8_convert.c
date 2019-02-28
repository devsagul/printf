/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:32:55 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/28 19:53:36 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

unsigned int	ft_utf8_convert(unsigned int c, int bytes)
{
	unsigned int	res;

	res = c;
	if (bytes == 1)
		res = c & 0x7F;
	else if (bytes == 2)
		res = 0xC000 | ((c & 0x7C0) << 2) | 0x80 | (c & 0x3F);
	else if (bytes == 3)
	{
		res = 0xE00000 | ((c & 0xF000) << 4) | 0x8000;
		res |= ((c & 0xFC0) << 2) | 0x80 | (c & 0x3F);
	}
	else if (bytes == 4)
	{
		res = 0xF0000000 | (c & 0x0E0000) | 0x800000;
		res |= ((c & 0x3F000) << 4) | 0x8000;
		res |= ((c & 0xFC0) << 2) | 0x80 | (c & 0x3F);
	}
	return (res);
}
