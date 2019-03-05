/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstrbyspec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:48:05 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/02 22:10:00 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

static t_outputfunc	get_output_function(t_specificator specificator)
{
	if (specificator == CHAR)
		return (ft_char_format);
	if (specificator == STRING)
		return (ft_string_format);
	if (specificator == INTEGER)
		return (ft_integer_format);
	if (specificator == OCT)
		return (ft_oct_format);
	if (specificator == HEX)
		return (ft_hex_format);
	if (specificator == HEX_UPPER)
		return (ft_hex_upper_format);
	if (specificator == UNSIGNED)
		return (ft_unsigned_format);
	if (specificator == POINTER)
		return (ft_pointer_format);
	if (specificator == A_FLOAT)
		return (ft_afloat_format);
	if (specificator == A_FLOAT_UPPER)
		return (ft_afloat_upper_format);
	if (specificator == FLOAT)
		return (ft_float_format);
	return (NULL);
}

void				ft_getstrbyspec(t_specification spec,
											t_smartstr *pbuf,
											va_list ap)
{
	t_outputfunc	output_function;
	size_t			len;
	char			*s;

	s = NULL;
	if (spec.specificator == PERCENT || spec.specificator == UNKNOWN)
		len = spec.specificator == PERCENT ?
				ft_percent_format(&s, spec) : ft_unknown_format(&s, spec);
	else
	{
		output_function = get_output_function(spec.specificator);
		if (output_function == NULL)
			return ;
		len = output_function(&s, spec, ap);
	}
	ft_smartstrncat(pbuf, s, len);
	if (s != NULL)
		free(s);
}
