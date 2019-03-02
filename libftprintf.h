/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <mbalon-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:33:09 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/03/02 13:53:32 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <string.h>
# include <stdarg.h>
# include <inttypes.h>

# define INITIAL_BUFFER_SIZE 2048

typedef	enum			e_specificator
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
	A_FLOAT,
}						t_specificator;

typedef struct			s_smartstr
{
	char				*str;
	size_t				len;
	size_t				size;
}						t_smartstr;

typedef struct			s_floating_point
{
	int					exponent;
	unsigned long long	fraction;
	unsigned int		sign : 1;
}						t_floating_point;


typedef struct			s_specification
{
	int					minwidth;
	int					precision;
	t_specificator		specificator;
	char				ch;
	unsigned			align_left : 1;
	unsigned			force_sign : 1;
	unsigned			force_spacing : 1;
	unsigned			force_zeroes : 1;
	unsigned			alt_print : 1;
	unsigned			wildcard_minwidth : 1;
	unsigned			wildcard_precision : 1;
	unsigned			get_wildcard_minwidth : 1;
	unsigned			get_wildcard_precision : 1;
	unsigned			precision_set : 1;
	unsigned			short_mod : 1;
	unsigned			short_short_mod : 1;
	unsigned			long_mod : 1;
	unsigned			long_long_mod : 1;
	unsigned			long_double_mod : 1;
	unsigned			size_t_mod : 1;
	unsigned			intmax_t_mod : 1;
}						t_specification;

typedef size_t			(*t_outputfunc) (char **pstr, t_specification, va_list);

int						ft_printf(const char *format, ...);
void					ft_getstrbyspec(t_specification spec,
									t_smartstr *pbuf,
									va_list		ap);
t_smartstr				*ft_smartstrncat(t_smartstr *smartstr,
									const char *s, size_t len);
void					ft_flushsmartstr(t_smartstr *smartstr);
ssize_t					ft_expandsmartstr(t_smartstr *smartstr);
char					*ft_strchr(const char *s, int c);
char					*ft_strcpy(char *dst, const char *src);
int						ft_instr(char c, char *s);
size_t					ft_ulfromstr(const char *s, unsigned long *dst);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strncpy(char *dst, const char *src, size_t len);
size_t					ft_getspecificator(const char *format,
										t_specification *pspec);
int						ft_count_digits_unsigned(unsigned long long int nbr,
													unsigned base);
long long int			ft_get_signed_arg(va_list ap, t_specification spec);
unsigned long long int	ft_get_unsigned_arg(va_list ap, t_specification spec);
size_t					ft_percent_format(char **pdst, t_specification spec);
size_t					ft_unknown_format(char **pdst, t_specification spec);
size_t					ft_char_format(char **pdst, t_specification spec,
									va_list ap);
size_t					ft_string_format(char **pdst, t_specification spec,
										va_list ap);
size_t					ft_unicode_format(char **pdst, t_specification spec,
										va_list ap);
size_t					ft_integer_format(char **pdst, t_specification spec,
										va_list ap);
size_t					ft_oct_format(char **pdst, t_specification spec,
										va_list ap);
size_t					ft_hex_format(char **pdst, t_specification spec,
										va_list ap);
size_t					ft_hex_upper_format(char **pdst, t_specification spec,
										va_list ap);
size_t					ft_unsigned_format(char **pdst, t_specification spec,
										va_list ap);
size_t					ft_pointer_format(char **pdst, t_specification spec,
										va_list ap);
size_t					ft_afloat_format(char **pdst, t_specification spec,
										va_list ap);
int						ft_utf8_count_bytes(unsigned int c);
unsigned int			ft_utf8_convert(unsigned int c, int bytes);
void					ft_format_hex(unsigned long long int nbr,
										t_specification spec,
										char *str, char b);
void					ft_fill_floating_point(double nbr,
												t_floating_point *dst);
void					ft_fill_long_floating_point(long double nbr,
												t_floating_point *dst);
int						ft_count_digits_signed(long long int nbr);

#endif
