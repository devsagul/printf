/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits_unsigned.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 01:56:40 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/28 19:46:07 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_count_digits_unsigned(unsigned long long int nbr, unsigned base)
{
	int		res;

	res = 0;
	while (nbr != 0)
	{
		nbr /= base;
		res++;
	}
	return (res);
}
