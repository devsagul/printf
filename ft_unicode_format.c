/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbalon-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 22:17:08 by mbalon-s          #+#    #+#             */
/*   Updated: 2019/02/27 22:17:09 by mbalon-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libftprintf.h"

static int  		utf8_count_bytes(unsigned int c)
{
    if (c <= 0x7F)
        return (1);
    else if (c <= 0x7FF)
        return (2);
    else if (c <= 0xFFFF)
        return (3);
    else if (c <= 0x10FFFF)
        return (4);
    return (0);
}

static unsigned int	utf8_convert(unsigned int c, int bytes)
{
    if (bytes == 1)
        return (c & 0x7F);
    if (bytes == 2)
        return (0xC000 | ((c & 0x7C0) << 2) | 0x80 | (c & 0x3F));
    if (bytes == 3)
        return (0xE00000 | ((c & 0xF000) << 4) | 0x8000 | ((c & 0xFC0) << 2) | 0x80 | (c & 0x3F));
    if (bytes == 4)
        return (0xF0000000 | ((c & 0x0E0000) ) | 0x800000 | ((c & 0x3F000) << 4) | 0x8000 | ((c & 0xFC0) << 2) | 0x80 | (c & 0x3F));
    return (c);
}

static int       utf8_strlen(unsigned int *str)
{
    size_t  res;

    res = 0;
    while (*str != '\0')
    {
        res += utf8_count_bytes(*str);
        str++;
    }
    return (res);
}

unsigned int            *get_null_utf8_str(void)
{
    unsigned int    *res;

    res = (unsigned int *)malloc(sizeof(unsigned int) * 7);
    if (res == NULL)
        return (NULL);
    res[0] = '(';
    res[1] = 'n';
    res[2] = 'u';
    res[3] = 'l';
    res[4] = 'l';
    res[5] = ')';
    res[6] = '\0';
    return (res);
}

size_t                  utf8_strncpy(char *dst, unsigned int *src, size_t length)
{
    size_t  i;
    size_t  j;
    unsigned int c;
    int bytes;

    i = 0;
    j = 0;
    while (src[j] != '\0' && utf8_count_bytes(src[j]) + i < length)
    {
        bytes = utf8_count_bytes(src[j]);
        c = utf8_convert(src[j], bytes);
        while (bytes) {
            bytes--;
            dst[i] = (char) (((0xFF << 8 * bytes) & c) >> 8 * bytes);
            i++;
        }
        j++;
    }
    if (src[j] != '\0')
    {
        bytes = utf8_count_bytes(src[j]);
        c = utf8_convert(src[j], bytes);
        while (bytes) {
            bytes--;
            dst[i] = (char) (((0xFF << 8 * bytes) & c) >> 8 * bytes);
            i++;
        }
        return (utf8_count_bytes(src[j]));
    }
    return (0);
}

size_t					ft_unicode_format(char **pdst, t_specification spec,
                                            va_list ap)
{
    int		len;
    char    *str;
    unsigned int	*arg;
    size_t          added;

    arg = (unsigned int *)va_arg(ap, unsigned int *);
    if (arg == NULL)
        arg = get_null_utf8_str();
    if (arg == NULL)
        return (0);
    len = utf8_strlen(arg);
    if (!spec.precision_set)
        spec.precision = len;
    if (len < spec.precision)
        spec.precision = len;
    if (spec.minwidth < spec.precision)
        spec.minwidth = spec.precision;
    str = (char *)malloc(sizeof(char) * (spec.minwidth + 4));
    if (str == NULL)
        return (0);
    if (!spec.force_zeroes || spec.align_left)
        ft_memset(str, ' ', sizeof(char) * spec.minwidth);
    else
        ft_memset(str, '0', sizeof(char) * spec.minwidth);
    str[spec.minwidth] = '\0';
    str[spec.minwidth + 1] = '\0';
    str[spec.minwidth + 2] = '\0';
    str[spec.minwidth + 3] = '\0';
    if (!spec.align_left)
        added = utf8_strncpy(str + spec.minwidth - spec.precision, arg, spec.precision);
    else
        added = utf8_strncpy(str, arg, spec.precision);
    //spec.minwidth += added;
    *pdst = str;
    return (spec.minwidth);
}
