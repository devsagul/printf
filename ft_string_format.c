/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 19:32:43 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/28 21:16:01 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"

size_t				ft_string_format(char **pdst, t_specification spec,
										va_list ap)
{
	int		len;
	char	*str;
	char	*arg;
	char	fill;

	if (spec.long_long_mod || spec.long_mod)
		return (ft_unicode_format(pdst, spec, ap));
	arg = (char *)va_arg(ap, char *);
	if (arg == NULL)
		arg = "(null)";
	len = ft_strlen(arg);
	if (!spec.precision_set || len < spec.precision)
		spec.precision = len;
	if (spec.minwidth < spec.precision)
		spec.minwidth = spec.precision;
	str = (char *)malloc(sizeof(char) * (spec.minwidth + 1));
	if (str == NULL)
		return (0);
	fill = !spec.force_zeroes || spec.align_left ? ' ' : '0';
	ft_memset(str, fill, spec.minwidth);
	str[spec.minwidth] = '\0';
	*pdst = str;
	str = spec.align_left ? str : str + spec.minwidth - spec.precision;
	ft_strncpy(str, arg, spec.precision);
	return (spec.minwidth);
}
