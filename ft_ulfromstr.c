/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulfromstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 15:02:53 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/23 15:49:06 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	ft_ulfromstr(const char *s, unsigned long *dst)
{
	unsigned long	nbr;
	char			*tmp;

	tmp = s;
	nbr = 0;
	while (instr(*tmp, " \t\n\r\f"))
		tmp++;
	while (*tmp >= '0' && *tmp <= '9')
	{
		nbr = nbr * 10 + (*tmp - '0');
		tmp++;
	}
	*dst = nbr;
	return (tmp - s);
}
