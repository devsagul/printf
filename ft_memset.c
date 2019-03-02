/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 18:15:03 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/01 17:50:59 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *tmp;
	unsigned char ch;

	ch = (unsigned char)c;
	tmp = (unsigned char *)b;
	while (len > 0)
	{
		*tmp = ch;
		tmp++;
		len--;
	}
	return (b);
}
