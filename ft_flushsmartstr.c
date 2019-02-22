/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flushsmartstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 19:36:00 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/22 19:40:01 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

void	ft_flushsmartstr(t_smartstr *smartstr)
{
	if (smartstr->str != NULL)
		free(smartstr->str);
	smartstr->size = 0;
	smartstr->len = 0;
}
