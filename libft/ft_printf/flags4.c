/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:21:52 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/16 23:32:11 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digits(char *s, int upto)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (upto == -1 ? s[i] : i < upto)
	{
		if (ft_isdigit(s[i]))
			count++;
		i++;
	}
	return (count);
}

static char	*apostrophe_helper(char *s, int n, int f)
{
	int		l;
	char	*ret;
	int		i;
	int		j;
	int		set;

	l = n + n / 3 - (n % 3 == 0 ? 1 : 0);
	ret = ft_strnewpad(l, ',');
	i = 0;
	j = 0;
	set = 0;
	while (j < l)
	{
		if (j > 0 && set == 0 && (n - i) % 3 == 0)
		{
			j++;
			set = 1;
			continue;
		}
		ret[j++] = s[i++];
		set = 0;
	}
	if (f)
		ft_memcpy(ret + l, s + n, ft_strlen(s) - n);
	return (ret);
}

char		*apply_apostrophe(char *s, int specifier)
{
	char	*tmp;
	int		n;
	int		f;

	tmp = s;
	f = 0;
	if (specifier == D || specifier == U || specifier == I)
		n = count_digits(s, -1);
	if (specifier == F)
	{
		if ((n = ft_stridx(s, '.')) >= 0)
		{
			f = 1;
			n = count_digits(s, n);
		}
		else
			n = count_digits(s, -1);
	}
	if (n > 3)
	{
		s = apostrophe_helper(s, n, f);
		free(tmp);
	}
	return (s);
}
