/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:33:09 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/22 20:13:01 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <string.h>

# define INITIAL_BUFFER_SIZE 2048

typedef struct	s_smartstr
{
	char		*str;
	size_t		len;
	size_t		size;
}				t_smartstr;

int				ft_printf(const char *format, ...);
size_t			ft_smartstrncat(t_smartstr *smartstr,
								const char *s, size_t len);
void			ft_flushsmartstr(t_smartstr *smartstr);
ssize_t			ft_expandsmartstr(t_smartstr *smartstr);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dst, const char *src);

#endif
