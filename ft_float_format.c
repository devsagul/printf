/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 22:10:55 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/04 15:23:11 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

static size_t			print_float_nan_or_inf(char **pdst,
												t_specification spec,
												t_floating_point num)
{
	int		len;
	char	*str;
	char	*arg;

	if (num.nan)
		arg = "nan";
	else if (num.sign)
		arg = "-inf";
	else if (spec.force_sign)
		arg = "+inf";
	else if (spec.force_spacing)
		arg = " nan";
	else
		arg = "inf";
	len = ft_strlen(arg);
	spec.precision = len;
	if (spec.minwidth < spec.precision)
		spec.minwidth = spec.precision;
	str = (char *)malloc(sizeof(char) * (spec.minwidth + 1));
	if (str == NULL)
		return (0);
	ft_memset(str, ' ', spec.minwidth);
	str[spec.minwidth] = '\0';
	*pdst = str;
	str = spec.align_left ? str : str + spec.minwidth - spec.precision;
	ft_strncpy(str, arg, spec.precision);
	return (spec.minwidth);
}

static id_t				count_integer_float_digits(t_floating_point fp)
{
	int					res;

	res = 0;
	fp.fraction |= ((unsigned long long)fp.integer << 52);
	while (fp.exponent > 0)
	{
		while ((((fp.fraction >> 52) & 0xF) < 0xA) && fp.exponent > 0)
		{
			fp.fraction <<= 1;
			fp.exponent--;
		}
		ft_printf("%d\n", ((fp.fraction & (0xFLL << 52)) >> 52) - 6);
		fp.fraction -= (0x6LL << 52);
		fp.fraction |= ((unsigned long long)fp.integer << 52);
		res++;
	}
	ft_printf("%d\n", res);
	return (res == 0 ? 1 : res);
}

size_t					ft_float_format(char **pdst, t_specification spec,
							va_list ap)
{
	double				nbr;
	char				*str;
	t_floating_point	fp;
	int					num_digits;

	nbr = va_arg(ap, double);
	ft_fill_floating_point(nbr, &fp);
	if (fp.nan || fp.inf)
		return (print_float_nan_or_inf(pdst, spec, fp));
	if (!spec.precision_set)
		spec.precision = 6;
	num_digits = count_integer_float_digits(fp);
	num_digits += spec.precision == 0 ? 0 : 1;
	num_digits += spec.precision;
	if (fp.sign || spec.force_sign || spec.force_spacing)
		num_digits++;
	if (spec.minwidth < num_digits)
		spec.minwidth = num_digits;
	str = (char *)malloc(sizeof(char) * spec.minwidth + 1);
	if (str == NULL)
		return (0);
	str[spec.minwidth] = '\0';
	//print_float(fp, spec, str, num_digits);
	*pdst = str;
	return (spec.minwidth);
}
