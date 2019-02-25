/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_unsigned_argument.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 01:30:41 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/26 01:30:43 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libftprintf.h"

unsigned long long int	ft_get_unsigned_arg(va_list ap, t_specification spec) {
    unsigned long long int  nbr;

    if (spec.long_long_mod)
        nbr = va_arg(ap, long long int);
    else if (spec.intmax_t_mod)
        nbr = (intmax_t)va_arg(ap, intmax_t);
    else if (spec.size_t_mod)
        nbr = (ssize_t)va_arg(ap, ssize_t);
    else if (spec.long_mod)
        nbr = (unsigned long int)va_arg(ap, long int);
    else if (spec.short_short_mod)
        nbr = (unsigned char)va_arg(ap, int);
    else if (spec.short_mod)
        nbr = (unsigned short int)(unsigned int)va_arg(ap, int);
    else
        nbr = (unsigned int)va_arg(ap, int);
    return (nbr);
}
