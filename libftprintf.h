/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:33:09 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/24 23:46:46 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <string.h>
# include <stdarg.h>

# define INITIAL_BUFFER_SIZE 2048

typedef	enum		e_specificator
{
	UNKNOWN,
	PERCENT,
	CHAR,
	STRING,
	INTEGER,
	OCT,
	HEX,
	HEX_UPPER,
	UNSIGNED,
	POINTER,
}					t_specificator;

typedef struct		s_smartstr
{
	char			*str;
	size_t			len;
	size_t			size;
}					t_smartstr;

typedef struct		s_specification
{
	int				minwidth;
	int				precision;
	t_specificator	specificator;
	char			ch;
	unsigned		align_left : 1;
	unsigned		force_sign : 1;
	unsigned		force_spacing : 1;
	unsigned		force_zeroes : 1;
	unsigned		alt_print : 1;
	unsigned		wildcard_minwidth : 1;
	unsigned		wildcard_precision : 1;
	unsigned		precision_set : 1;
	unsigned		short_mod : 1;
	unsigned		short_short_mod : 1;
	unsigned		long_mod : 1;
	unsigned		long_long_mod : 1;
	unsigned		long_double_mod : 1;
	unsigned		size_t_mod : 1;
	unsigned		intmax_t_mod : 1;
}					t_specification;

typedef size_t		(*t_outputfunc) (char **pstr, t_specification, va_list);

int					ft_printf(const char *format, ...);
void				ft_getstrbyspec(t_specification spec,
									t_smartstr *pbuf,
									va_list		ap);
t_smartstr			*ft_smartstrncat(t_smartstr *smartstr,
									const char *s, size_t len);
void				ft_flushsmartstr(t_smartstr *smartstr);
ssize_t				ft_expandsmartstr(t_smartstr *smartstr);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dst, const char *src);
int					ft_instr(char c, char *s);
size_t				ft_ulfromstr(const char *s, unsigned long *dst);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strncpy(char *dst, const char *src, size_t len);
size_t				ft_getspecificator(const char *format,
										t_specification *pspec);
size_t				ft_percent_format(char **pdst, t_specification spec);
size_t				ft_unknown_format(char **pdst, t_specification spec);
size_t				ft_char_format(char **pdst, t_specification spec,
									va_list ap);
size_t				ft_string_format(char **pdst, t_specification spec,
										va_list ap);
size_t				ft_integer_format(char **pdst, t_specification spec,
										va_list ap);
size_t				ft_oct_format(char **pdst, t_specification spec,
										va_list ap);
size_t				ft_hex_format(char **pdst, t_specification spec,
										va_list ap);
size_t				ft_hex_upper_format(char **pdst, t_specification spec,
										va_list ap);
size_t				ft_unsigned_format(char **pdst, t_specification spec,
										va_list ap);
size_t				ft_pointer_format(char **pdst, t_specification spec,
										va_list ap);

#endif
