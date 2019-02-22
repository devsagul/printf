/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expandsmartstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:40:22 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/22 20:45:03 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

ssize_t	ft_expandsmartstr(t_smartstr *smartstr)
{
	char	*new_str;
	size_t	new_size;

	if (smartstr->size == (size_t)-1)
		return (-1);
	if (smartstr->size == 0)
		new_size = INITIAL_BUFFER_SIZE;
	else
		new_size = smartstr->size << 1;
	if (new_size <= smartstr->size)
		return (-1);
	new_str = (char *)malloc(sizeof(char) * new_size);
	if (new_str == NULL)
		return (-1);
	if (smartstr->str != NULL)
	{
		ft_strcpy(new_str, smartstr->str);
		free(smartstr->str);
	}
	smartstr->str = new_str;
	smartstr->size = new_size;
	return (new_size);
}
