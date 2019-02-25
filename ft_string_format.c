/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 19:32:43 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/25 20:04:06 by mbalon-s         ###   ########.fr       */
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

	arg = (char *)va_arg(ap, char *);
	if (arg == NULL)
		arg = "(null)";
	len = ft_strlen(arg);
	if (!spec.precision_set)
		spec.precision = len;
	if (len < spec.precision)
		spec.precision = len;
	if (spec.minwidth < spec.precision)
		spec.minwidth = spec.precision;
	str = (char *)malloc(sizeof(char) * (spec.minwidth + 1));
	if (str == NULL)
		return (0);
	if (!spec.force_zeroes || spec.align_left)
		ft_memset(str, ' ', sizeof(char) * spec.minwidth);
	else
		ft_memset(str, '0', sizeof(char) * spec.minwidth);
	str[spec.minwidth] = '\0';
	if (!spec.align_left)
		ft_strncpy(str + spec.minwidth - spec.precision, arg, spec.precision);
	else
		ft_strncpy(str, arg, spec.precision);
	*pdst = str;
	return (spec.minwidth);
}
