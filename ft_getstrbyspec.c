/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstrbyspec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:48:05 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/23 17:17:00 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

static t_outputfunc	get_output_function(t_specificator specificator)
{
	if (specificator == CHAR)
		return (NULL);
	return (NULL);
}

size_t				ft_getstrbyspec(t_specification spec,
									t_smartstr *pbuf,
									va_list ap)
{
	t_outputfunc	output_function;	
	size_t			len;
	char			*s;

	if (spec.specificator == PERCENT)
	{
		len = ft_percent_format(&s, spec);
		free(s);
		return (len);
	}
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
