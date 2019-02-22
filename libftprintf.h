/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:33:09 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/22 18:37:06 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <string.h>

typedef struct	s_smartstr
{
	char		*str;
	ssize_t		len;
	size_t		size;
}				t_smartstr

size_t	progress_buffer(const char *format, t_smartstr buffer, va_list ap);
int		ft_printf(const char *format, ...);

#endif
