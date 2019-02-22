/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:17:31 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/22 17:32:36 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include "libftprintf.h"

int		ft_printf(const char *format, ...)
{
	t_smartstr	buffer;
	ssize_t		bytes;

	// initialize arguments
	// checks format for null etc
	// initialize buffer
	// while format is not empty
		// fill buffer
		// checck buffer not empty
	bytes = write(1, buffer.str, buffer.len);
	return (bytes);
}
