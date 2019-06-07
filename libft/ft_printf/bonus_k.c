/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_k.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:33:53 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/14 22:24:22 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_strdup_n(const char *s1, size_t n)
{
	char	*d;

	d = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	return (ft_strncpy(d, s1, n));
}

static char	*get_month(char *m)
{
	unsigned int n;

	n = ft_atoi(m);
	free(m);
	if (n < 12)
		return (ft_strdup(g_months[n]));
	return (NULL);
}

static char	*join_and_free_m(char *a, char *b, char *c)
{
	char	*ret;
	char	delim;
	int		alen;
	int		blen;
	int		clen;

	delim = ' ';
	alen = ft_strlen(a);
	blen = ft_strlen(b);
	clen = ft_strlen(c);
	ret = (char *)malloc((alen + blen + clen + 3) * sizeof(char));
	ft_memcpy(ret, a, alen);
	ret[alen] = delim;
	ft_memcpy(ret + alen + 1, b, blen);
	ret[alen + blen + 1] = delim;
	ft_memcpy(ret + alen + blen + 2, c, clen);
	ret[alen + blen + clen + 2] = 0;
	free(a);
	free(b);
	free(c);
	return (ret);
}

char		*k(va_list args)
{
	char	*ptr;
	int		format;
	char	*year;
	char	*month;
	char	*day;

	ptr = va_arg(args, char *);
	format = va_arg(args, unsigned int);
	year = ft_strdup_n(ptr, 4);
	month = get_month(ft_strdup_n(ptr + 4, 2));
	day = ft_strdup_n(ptr + 6, 2);
	if (format == UNITED_STATES)
		ptr = join_and_free_m(month, day, year);
	else
		ptr = join_and_free_m(day, month, year);
	return (ptr);
}
