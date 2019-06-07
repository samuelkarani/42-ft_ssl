/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:43:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/06 22:14:42 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned long long	ft_strlen_llu(char *s)
{
	unsigned long long count;

	count = 0;
	while (*s++)
		count++;
	return count;
}

char	*join_free(char *a, char *b)
{
    char *ta, *tb, *ret;

    ta = a;
    tb = b;
    ret = ft_strjoin(a, b);
    free(ta);
    free(tb);
    return ret;
}

int	len_llu(unsigned long long n)
{
	int i;

	if (n == 0)
		return (1);
	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char	*ft_itoa_llu(unsigned long long n)
{
	char				*ret;
	int					len;

	len = len_llu(n);
	ret = ft_memalloc(len + 1);
	if (n == 0)
		ret[0] = '0';
	while (n)
	{
		ret[--len] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	return (ret);
}

int	*ft_memcpy_ints(int *dst, int *src, int n)
{
	int	i;

	i = 0;
	while (i++ < n)
		*dst++ = *src++;
	return (dst);
}
