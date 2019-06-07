/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:06:58 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/16 23:21:40 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			mantissa_length(char *s)
{
	int i;
	int len;

	len = ft_strlen(s);
	i = ft_stridx(s, '.');
	return (len - i - 1);
}

static char	*precision_e(char *s, int precision)
{
	int		e;
	int		mantissa;
	char	*tmp;
	int		len;
	int		neg;

	tmp = s;
	mantissa = mantissa_length(s) - 4;
	e = ft_stridx(s, 'e');
	precision = precision == -1 ? 6 : precision;
	neg = s[0] == '-';
	if (precision == 0)
		s = join_and_free(ft_strsub(s, 0, neg + 1),
			ft_strsub(s, e, ft_strlen(s)));
	else if (mantissa > precision)
		s = join_and_free(round_up(s, precision), ft_strsub(s, e, 4));
	else if (precision > mantissa)
	{
		len = 2 + neg + precision + 4;
		s = ft_strnewpad(len, '0');
		ft_memcpy(s, tmp, e);
		ft_memcpy(s + len - 4, tmp + e, 4);
	}
	free(tmp);
	return (s);
}

static char	*precision_f(char *s, int precision)
{
	int		len;
	int		mantissa;
	int		idx;
	char	*tmp;

	tmp = s;
	mantissa = mantissa_length(s);
	if (precision == 0)
	{
		idx = ft_stridx(s, '.');
		s = ft_strsub(s, 0, idx);
	}
	else if (precision == -1)
		s = round_up(s, 6);
	else if (precision < mantissa)
		s = round_up(s, precision);
	else if (precision > mantissa)
	{
		idx = ft_stridx(s, '.');
		len = idx + precision + 1;
		s = ft_memcpy(ft_strnewpad(len, '0'), s, len);
	}
	if (tmp != s)
		free(tmp);
	return (s);
}

static char	*precision_diouxxp(char *s, int precision)
{
	char	*tmp;
	int		neg;
	int		len;

	tmp = s;
	if (precision > (len = num_digits(s)))
	{
		if ((neg = check_neg(tmp)) >= 0)
		{
			s = ft_strnewpad(precision + 1, '0');
			s[0] = '-';
			while (tmp[len] != '-')
				s[precision--] = tmp[len--];
		}
		else
		{
			s = ft_strnewpad(precision, '0');
			ft_memcpy(s + precision - len, tmp, len);
		}
	}
	else if (precision == 0 && ft_strcmp(s, "0") == 0)
		s = ft_strdup("");
	if (s != tmp)
		free(tmp);
	return (s);
}

char		*apply_precision(char *s, int precision, int specifier)
{
	int		len;
	char	*tmp;

	if (specifier == F)
		s = precision_f(s, precision);
	else if (specifier == E)
		s = precision_e(s, precision);
	else if (specifier == G)
		s = precision_g(s, precision);
	else if ((specifier >= D && specifier <= XX) || specifier == P)
		s = precision_diouxxp(s, precision);
	else if (specifier != C)
	{
		len = ft_strlen(s);
		if (len > precision && !(specifier == PP && precision == 0))
		{
			tmp = s;
			s = ft_strsub(s, 0, precision);
			free(tmp);
		}
	}
	return (s);
}
