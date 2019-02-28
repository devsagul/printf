/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smartstrncat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:46:13 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/24 23:59:27 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_smartstr	*ft_smartstrncat(t_smartstr *smartstr, const char *s, size_t len)
{
	size_t	i;
	size_t	j;
	ssize_t	tmp;

	if (s == NULL || len == 0)
		return (smartstr);
	if (smartstr->len + len < smartstr->len)
	{
		ft_flushsmartstr(smartstr);
		return (smartstr);
	}
	while (smartstr->len + len >= smartstr->size)
	{
		tmp = ft_expandsmartstr(smartstr);
		if (tmp == -1)
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
