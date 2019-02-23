/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smartstrncat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:46:13 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/23 18:17:08 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_smartstr	*ft_smartstrncat(t_smartstr *smartstr, const char *s, size_t len)
{
	size_t	i;
	ssize_t	tmp;

	if (s == NULL)
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
	while (*s != '\0')
		smartstr->str[i++] = *s++;
	smartstr->str[i] = '\0';
	smartstr->len += len;
	return (smartstr);
}
