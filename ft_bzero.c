/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 18:29:43 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/28 19:04:49 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned		*mas;
	unsigned		*origin;
	unsigned char	*tmp;
	unsigned char	*ch_origin;

	origin = (unsigned *)s;
	mas = origin;
	while ((mas - origin) * sizeof(unsigned) < n)
	{
		*mas = 0;
		mas++;
	}
	if ((unsigned)(mas - origin) != n)
	{
		ch_origin = (unsigned char *)origin;
		tmp = (unsigned char *)(mas - 1);
		while ((unsigned char)(tmp - ch_origin) < n)
		{
			*tmp = 0;
			tmp++;
		}
	}
}
