/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaegar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 19:47:18 by orhaegar          #+#    #+#             */
/*   Updated: 2019/02/25 00:15:07 by orhaegar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STRNUM_SIZE 4933

#include "libftprintf.h"

typedef struct		s_str_ld
{
	unsigned char	intg[STRNUM_SIZE];
	unsigned char	flt[STRNUM_SIZE];
	unsigned short	i_size;
	unsigned short	f_size;
}					t_str_ld;

void	intg_inc(t_str_ld *nbr,  unsigned char base)
{
	short i;

	i = 0;
	--base;
	while (i < nbr->i_size && nbr->intg[i] == base)
	{
		nbr->intg[i] = 0;
		++i;
	}
	if (i == nbr->i_size && i < STRNUM_SIZE)
	{
		nbr->intg[i] = 1;
		nbr->i_size += 1;
	}
	else
		nbr->intg[i] += 1;
	return ;
}

void	flt_inc(t_str_ld *nbr, unsigned char base)
{
	short i;

	i = nbr->f_size;
	--base;
	while (i > -1 && nbr->flt[i] == base)
	{
		nbr->flt[i] = 0;
		--i;
	}
	if (i == -1)
		intg_inc(nbr, base + 1);
	else
		nbr->flt[i] += 1;
	return ;
}

short		num_digits_bp(long double a)
{
	short i;

	i = 1;
	while ((a /= 10) >= 1)
		++i;
	return (i);
}

size_t		ft_float_format(char **pstr, long double a)
{
	short	i;
	short	j;
	char	tmp;
	char	*str;

	str = *pstr;
	i = num_digits_bp(a);
	while (a >= 1)
		a /= 10;
	j = 0;
	while (j < i)
	{
		a *= 10;
		tmp = (char)(a);
		*str++ = tmp + '0';
		a -= (long double)(tmp);
		++j;
	}
	*str++ = '.';
	while (a > 1)
	{
		a *= 10;
		tmp = (char)(a);
		*str++ = tmp + '0';
		a -= (long double)(tmp);
		++j;
	}
	*str = '\0';
	return (size_t)(j);
	/*
	long double		i;
	long double		f;
	long double		tmp;
	t_str_ld		res;
	short			j;

	i = a; // get va_list here

	res.i_size = 0;
	res.f_size = 0;
	f = i;
	tmp = 0;
	while (i > 9)
	{
		tmp = (tmp + (i % 10)) * 10;
		res.intg[res.i_size++] = (unsigned char)(i % 10);
		i /= 10;
	}
	f -= tmp;
	while (f > 0)
	{
		f *= 10;
		res.flt[res.f_size++] = (unsigned char)(f % 10);
		f -= f % 10;
	}
	*pstr = (char *)malloc(res.f_size + res.i_size + 2);
	if (*pstr == NULL)
		return (NULL);
	j = res.i_size - 1;
	while(j > -1)
		*(*pstr)++ = res.intg[j--] + '0';
	*(*pstr)++ = '.';
	j = 0;
	while (j < res.f_size - 1)
		*(*pstr)++ = res.flt[j++] + '0';
	**pstr = '\0';
	return (res.f_size + res.i_size + 1);
	*/
}

#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
int		main(void)
{
	char	*str = (char *)malloc(5000);
	double  b, c ,d;
	long double a, f, g, t;
	size_t shift;

	f = LDBL_MAX - 89770240.0 + 0.1425235;
	t = 1352352353451345134333.0;
	a = 4.992342342342342349999999999999999912313213131;
	
	printf("%Lf\n", t);
	shift = ft_float_format(&str, t);
	printf("%s\n", str);
	printf("1352352353451345134.14351345134513451\n");
/*	printf("%.40Lf\n", a);
	printf("\n%100.Lf\n", a);
	printf("%40.Lf\n", a);
	printf("\n%100.100Lf\n", a);
	printf("%100.40Lf\n", a);
	printf("%40.100Lf\n", a);
	printf("%310.Lf\n", a);
*/
	return (0);
}
