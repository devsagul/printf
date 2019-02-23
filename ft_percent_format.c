/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:20:21 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/23 19:17:25 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

size_t	ft_percent_format(char **pdst, t_specification spec)
{
	size_t	res;
	char	*str;

	res = spec.minwidth;
	if (res <= 0)
		res = 1;
	str = (char *)malloc(sizeof(char) * (res + 1));
	if (str == NULL)
		return (0);
	if (spec.force_zeroes && !spec.align_left)
		ft_memset(str, '0', sizeof(char) * res);
	else
		ft_memset(str, ' ', sizeof(char) * res);
	str[res] = '\0';
	if (spec.align_left)
		str[0] = '%';
	else
		str[res - 1] = '%';
	*pdst = str;
	return (res);
}
