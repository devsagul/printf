/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_afloat_upper_format.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 18:32:52 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/02 22:29:34 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"

static int				count_digits_fraction(unsigned long long fr)
{
	int		res;

	res = 0;
	while (fr != 0)
	{
		fr &= 0x0FFFFFFFFFFFF;
		fr <<= 4;
		res++;
	}
	return (res);
}

static void				promote(char *str)
{
	while (*str == 'G' || *str == '.')
	{
		if (*str != '.')
		{
			*str += '0' - 'G';
			if (str[-1] != '.')
			{
				str[-1] += 1;
				if (str[-1] == '9' + 1)
					str[-1] = 'A';
			}
			else
			{
				str[-2] += 1;
				if (str[-2] == '9' + 1)
					str[-2] = 'A';
			}
		}
		str--;
	}
}

static size_t			fill_decimal(char *dst,
										unsigned long long fr,
										int count)
{
	int		digit;
	char	*tmp;

	tmp = dst;
	while (count > 1)
	{
		digit = (fr & 0xF000000000000) >> 48;
		*tmp = digit >= 10 ? 'A' + digit - 10 : '0' + digit;
		fr &= 0xFFFFFFFFFFFF;
		fr <<= 4;
		tmp++;
		count--;
	}
	if (count != 0)
	{
		digit = (fr & 0xF000000000000) >> 48;
		fr &= 0xFFFFFFFFFFFF;
		if ((fr >= 0x810000000000 && ((fr >> 40) & 0x1)) || (fr >= 0x900000000000))
			digit++;
		*tmp = digit >= 10 ? 'A' + digit - 10 : '0' + digit;
		if (*tmp == 'G')
			promote(tmp);
		tmp++;
	}
	return (tmp - dst);
}

static void				print_afloat(t_floating_point fp,
										t_specification spec, char *str,
										int num_digits)
{
	size_t				i;
	int					digits;

	ft_memset(str, ' ', spec.minwidth);
	if (spec.force_zeroes && spec.align_left)
		ft_memset(str, '0', num_digits);
	else if (spec.force_zeroes)
		ft_memset(str, '0', spec.minwidth);
	if (spec.align_left || spec.force_zeroes)
		i = 0;
	else
		i = spec.minwidth - num_digits;
	if (fp.sign)
		str[i++] = '-';
	else if (spec.force_sign)
		str[i++] = '+';
	else if (spec.force_spacing)
		str[i++] = ' ';
	ft_strncpy(str + i, "0X", 2);
	i += 2;
	if (spec.force_zeroes)
		i += spec.minwidth - num_digits;
	if (fp.integer == 0)
		ft_strncpy(str + i, "0", 1);
	else
		ft_strncpy(str + i, "1", 1);
	i += 1;
	if (spec.precision != 0)
		str[i++] = '.';
	i += fill_decimal(str + i, fp.fraction, spec.precision);
	str[i++] = 'P';
	str[i++] = fp.exponent >= 0 ? '+' : '-';
	fp.exponent = fp.exponent < 0 ? -fp.exponent : fp.exponent;
	digits = ft_count_digits_signed(fp.exponent);
	digits += digits == 0 ? 1 : 0;
	while (digits > 0)
	{
		digits--;
		str[i + digits] = '0' + fp.exponent % 10;
		fp.exponent /= 10;
	}
}

static size_t			print_afloat_nan_or_inf(char **pdst,
												t_specification spec,
												t_floating_point num)
{
	int		len;
	char	*str;
	char	*arg;

	if (num.nan)
		arg = "NAN";
	else if (num.sign)
		arg = "-INF";
	else if (spec.force_sign)
		arg = "+INF";
	else if (spec.force_spacing)
		arg = " INF";
	else
		arg = "INF";
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

size_t					ft_afloat_upper_format(char **pdst, t_specification spec,
										va_list ap)
{
	double				nbr;
	int					num_digits;
	char				*str;
	t_floating_point	fp;

	nbr = va_arg(ap, double);
	ft_fill_floating_point(nbr, &fp);
	if (fp.nan || fp.inf)
		return (print_afloat_nan_or_inf(pdst, spec, fp));
	if (!spec.precision_set && !(fp.fraction == 0 && fp.exponent == 0))
		spec.precision = count_digits_fraction(fp.fraction);
	num_digits = 3 + spec.precision + 2;
	num_digits += !(fp.exponent == 0 || (fp.fraction == 0 && fp.exponent == -1023)) ? ft_count_digits_signed(fp.exponent) : 1;
	num_digits += 1;
	if (fp.sign || spec.force_sign || spec.force_spacing)
		num_digits++;
	if (spec.minwidth < num_digits)
		spec.minwidth = num_digits;
	str = (char *)malloc(sizeof(char) * spec.minwidth + 1);
	if (str == NULL)
		return (0);
	str[spec.minwidth] = '\0';
	print_afloat(fp, spec, str, num_digits);
	*pdst = str;
	return (spec.minwidth);
}
