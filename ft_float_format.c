/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orhaegar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 19:47:18 by orhaegar          #+#    #+#             */
/*   Updated: 2019/02/26 04:12:51 by orhaegar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define LDH_EXP	0x7FFFLL

#include "libftprintf.h"
#include <limits.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_bignum
{
	short	base;
	int		exp;
	size_t	len;
	char	*str;
}				t_bignum;

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *tmp;
	unsigned char ch;

	ch = (unsigned char)c;
	tmp = (unsigned char *)b;
	while (len > 0)
	{
		*tmp = ch;
		tmp++;
		len--;
	}
	return (b);
}

char	*decompose_ld(long double a, t_bignum *b)
{
	unsigned long long	tmp;
	size_t				i;

	tmp = *((unsigned long long *)(&a) + 1);
	b->exp = (int)((tmp & LDH_EXP) - 0x3fffLL);
	if (b->exp > 64)
		b->len = b->exp;
	else if (b->exp < 0)
		b->len = 64 - b->exp;
	else
		b->len = 64;
	printf("1.%lu\n", b->len);
	b->str = (char *)malloc((b->len + 1) * sizeof(char));
	if (!b->str)
		return (NULL);
	if (b->exp < 0)
		i = b->len;
	else
		i = 64;
	b->str[b->len] = '\0';
	ft_memset(b->str, '0', b->len);
	tmp = *((unsigned long long *)(&a));
	printf("2.%llx\n", tmp);
	while (i--)
	{
		(b->str)[i] = (char)(tmp & 1) + 48;
		tmp >>= 1;
	}
	return (b->str);
}

size_t		ft_float_format(char **pstr, long double a)
{

	return (0);
}

int		main(void)
{
	long double l, tmp;
	t_bignum	b;

	tmp = 1;
	l = 12415567346245353535356.0000001231230320;
	printf("%.20Lf\n", l);
//	t = (unsigned long long *)(&l);
	decompose_ld(l, &b);
//	pow = *(t + 1) & 0x7fffLL - 16383LL;
//	*t = (*t & (1LL << 63)) ^ *t;
//	l -= (long double)(1LL << 63);
//	while (pow--)
//		tmp *= 2;
	printf("%s\n", b.str);
//	while (l > 0)
//	{
//		l *= 10;
//		printf("%c", (char)l + '0');
//		l -= (long double)((char)l);
//	}
//	printf("%Lf\n", t);
//	printf("%llx", );
//	printf("%llx\n", a.dw.h);
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
