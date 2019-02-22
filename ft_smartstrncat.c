/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smartstrncat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:46:13 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/22 18:50:55 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	ft_smartstrncat(t_smartstr *smartstr, const char *s, size_t len)
{
	size_t	i;

	if (smartstr->len + len < smartstr->len)
	{
		// flush smarstr
		return (0);
	}
	while (smartstr->len + len >= size)
	{
		// expand smartstr
	}
	i = len;
	while (*s != '\0')
	{
		smartstr->str[i] = *s;
		i++;
		s++;
	}
	smartstr->str[i] = '\0';
	smartstr->len += len;
	return (NULL);
}
