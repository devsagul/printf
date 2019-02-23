/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstrbyspec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:48:05 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/23 15:57:19 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"

size_t		ft_getstrbyspec(t_specification spec,
							t_smartstr *pbuf,
							va_list ap)
{
	t_outputfunc	output_function;	
	size_t			len;
	char			*s;

	output_function = get_output_function(spec.specificator);
	if (output_function == NULL)
	{
		ft_flushsmartstr(pbuf);
		return (0);
	}
	len = output_function(&s, spec, ap);
	ft_smartstrncat(pbuf, s, len);
	free(s);
	return (len);
}
