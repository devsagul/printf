/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smartstrncat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:46:13 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/28 21:10:49 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_smartstr	*ft_smartstrncat(t_smartstr *smartstr, const char *s, size_t len)
{
	size_t	i;
	size_t	j;

	if (s == NULL || len == 0)
		return (smartstr);
	if (smartstr->len + len < smartstr->len)
	{
		ft_flushsmartstr(smartstr);
		return (smartstr);
	}
	while (smartstr->len + len >= smartstr->size)
	{
		if (ft_expandsmartstr(smartstr) == -1)
		{
			ft_flushsmartstr(smartstr);
			return (smartstr);
		}
	}
	i = smartstr->len;
	j = 0;
	while (j < len)
		smartstr->str[i++] = s[j++];
	smartstr->str[i] = '\0';
	smartstr->len += len;
	return (smartstr);
}
