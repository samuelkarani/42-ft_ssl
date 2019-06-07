/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:35:57 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/16 00:43:06 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_mantissa(long double *n, char **tmp)
{
	int i;

	i = 0;
	while (i < 18)
	{
		if (*n - (long long)*n == 0)
			break ;
		*n *= 10;
		i++;
	}
	*tmp = ft_itoa_base_l(*n < 0 ? *n * -1 : *n, 10, 0);
	return (i < 7 ? 7 : i);
}

char		*join_and_free(char *left, char *right)
{
	char	*tmp;
	char	*tmp2;

	tmp = right;
	tmp2 = left;
	left = ft_strjoin(left, right);
	free(tmp);
	free(tmp2);
	return (left);
}

char		*ft_itoa_ld(long double n)
{
	char	*left;
	char	*right;
	char	*tmp;
	int		i;
	int		len;

	left = ft_itoa_base_l((long long)n, 10, 0);
	if ((long long)n == 0 && n < 0)
	{
		tmp = left;
		left = ft_strjoin("-", left);
		free(tmp);
	}
	tmp = left;
	left = ft_strjoin(left, ".");
	free(tmp);
	n -= (long long)n;
	i = get_mantissa(&n, &tmp);
	len = getlen(n, 10);
	right = ft_strnewpad(i, '0');
	ft_memcpy(right + i - len, tmp, len);
	free(tmp);
	return (join_and_free(left, right));
}

char		*ft_itoa_base_l(long long n, int base, int upper)
{
	char		*ret;
	size_t		len;
	long long	mod;
	int			neg;

	if (base < 2 || base > 16)
		return (NULL);
	len = getlen(n, base);
	neg = 0;
	if (n < 0)
		neg = 1;
	len += neg;
	ret = ft_memalloc(len + 1);
	if (neg)
		ret[0] = '-';
	if (n == 0)
		ret[0] = '0';
	upper = upper ? 'A' : 'a';
	while (n)
	{
		mod = ft_abs(n % base);
		ret[--len] = mod < 10 ? mod + '0' : mod - 10 + upper;
		n = n / base;
	}
	return (ret);
}

char		*ft_itlu(unsigned long long n, int base, int upper)
{
	char				*ret;
	size_t				len;
	unsigned long long	mod;

	if (base < 2 || base > 16)
		return (NULL);
	len = getlenllu(n, base);
	ret = ft_memalloc(len + 1);
	if (n == 0)
		ret[0] = '0';
	upper = upper ? 'A' : 'a';
	while (n)
	{
		mod = ft_abs(n % base);
		ret[--len] = mod < 10 ? mod + '0' : mod - 10 + upper;
		n = n / base;
	}
	return (ret);
}
