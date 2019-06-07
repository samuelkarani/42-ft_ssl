/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 00:46:22 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/16 23:29:57 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*construct(char *s, char *e)
{
	char *tmp;

	tmp = ft_strjoin("e", e);
	s = join_and_free(s, tmp);
	free(e);
	return (s);
}

static int	is_zero(char *s)
{
	int	i;
	int l;

	l = ft_strlen(s);
	i = 0;
	while (s[i] == '0' || s[i] == '.')
		i++;
	return (i == l);
}

char		*get_e(int exponent)
{
	char	*ret;
	char	*num;
	int		l;
	int		i;

	ret = ft_strnewpad(3, '0');
	ret[0] = exponent < 0 ? '-' : '+';
	num = ft_itoa(exponent);
	l = ft_strlen(num);
	l--;
	i = 2;
	while (l >= 0 && num[l] != '-')
	{
		ret[i] = num[l];
		l--;
		i--;
	}
	free(num);
	return (ret);
}

void		add_decimal(char *s, int start, int idx, int small)
{
	int		l;
	char	*cpy;
	int		i;

	l = ft_strlen(s);
	cpy = ft_strnewpad(l, '0');
	i = 0;
	if (s[0] == '-')
		cpy[i++] = '-';
	cpy[i++] = s[start];
	cpy[i++] = '.';
	if (small)
		ft_memcpy(cpy + i, s + start + 1, l - start - 1);
	else
	{
		ft_memcpy(cpy + i, s + start + 1, idx - start - 1);
		ft_memcpy(cpy + idx + 1, s + idx + 1, l - idx - 1);
	}
	ft_memcpy(s, cpy, l);
	free(cpy);
}

char		*e(char *s)
{
	char	*ret;
	int		idx;
	int		exponent;
	int		neg;

	neg = s[0] == '-';
	idx = ft_stridx(s, '.');
	if (idx > 1 + neg)
	{
		exponent = idx - 1 - neg;
		add_decimal(s, 0 + neg, idx, 0);
	}
	else if (!is_zero(s) && idx == 1 + neg && s[idx - 1] == '0')
	{
		exponent = 2 + neg;
		while (s[exponent] == '0')
			exponent++;
		add_decimal(s, exponent, idx, 1);
		exponent = (exponent - 1 - neg) * -1;
	}
	else
		exponent = 0;
	ret = construct(s, get_e(exponent));
	return (ret);
}
