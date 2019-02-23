/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:33:09 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/23 15:57:20 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <string.h>

# define INITIAL_BUFFER_SIZE 2048

typedef	enum		e_specificator
{
	CHAR,
}					t_specificator;

typedef struct		s_smartstr
{
	char			*str;
	size_t			len;
	size_t			size;
}					t_smartstr;

typedef struct		s_specification
{
	unsigned long	minwidth;
	unsigned long	precision;
	t_specificator	specificator;
	unsigned		align_left : 1;
	unsigned		force_sign : 1;
	unsigned		force_spacing : 1;
	unsigned		force_zeroes : 1;
	unsigned		alt_print : 1;
	unsigned		wildcard_minwidth : 1;
	unsigned		wildcard_precision : 1;
	unsigned		short_mod : 1;
	unsigned		short_short_mod : 1;
	unsigned		long_mod : 1;
	unsigned		long_long_mod : 1;
	unsigned		long_double_mod : 1;
}					t_specification;

typedef size_t		(*t_outputfunc) (char **, t_specification, va_list);

int					ft_printf(const char *format, ...);
size_t				ft_getstrbyspec(t_specification spec,
									t_smartstr *pbuf,
									va_list ap);
size_t				ft_smartstrncat(t_smartstr *smartstr,
									const char *s, size_t len);
void				ft_flushsmartstr(t_smartstr *smartstr);
ssize_t				ft_expandsmartstr(t_smartstr *smartstr);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dst, const char *src);
int					ft_instr(char c, char *s);
size_t				ft_ulfromstr(const char *s, unsigned long *dst);

#endif
