/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:37:52 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/16 23:15:01 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_zero(char *s, int upto)
{
	int i;

	i = 0;
	while (i < upto && s[i] == '0')
		i++;
	return (i == upto ? i : 0);
}

static void	trailing_zeros(char *s, int upto, int e)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < upto)
	{
		if ((j = is_zero(s + i, upto - i)))
			break ;
		i++;
	}
	if (j)
	{
		if (e)
		{
			ft_memmove(s + i, s + upto, 4);
			s[i + 4] = 0;
		}
		else
			s[i] = 0;
	}
}

static void	trailing_decimal(char *s)
{
	int idx;

	if ((idx = ft_stridx(s, '.')) >= 0)
	{
		if (s[idx + 1] == 'e')
		{
			ft_memmove(s + idx, s + idx + 1, 4);
			s[idx + 4] = 0;
		}
		if (!s[idx + 1])
			s[idx] = 0;
	}
}

static char	*handle_round(char *s, int precision, int e)
{
	int		mantissa;
	char	*tmp;
	int		neg;
	int		idx;
	char	*ss;

	mantissa = mantissa_length(s) - (e ? 4 : 0);
	idx = ft_stridx(s, '.');
	neg = s[0] == '-';
	ss = ft_strsub(s, neg, idx);
	precision -= num_digits(ss);
	free(ss);
	tmp = s;
	if (mantissa > precision)
	{
		s = round_up(s, precision);
		if (e)
			s = join_and_free(s, ft_strsub(tmp, e, 4));
		free(tmp);
	}
	return (s);
}

char		*precision_g(char *s, int precision)
{
	char	*ss;
	int		idx;
	int		e;
	int		is_e;
	int		len;

	idx = ft_stridx(s, 'e');
	ss = ft_strsub(s, idx + 1, 3);
	e = ft_atoi(ss);
	free(ss);
	precision = precision == 0 ? 1 : precision;
	precision = precision == -1 ? 6 : precision;
	len = ft_strlen(s);
	ss = s;
	if ((is_e = (e < -4 || e >= precision)))
		s = ft_strsub(s, 0, idx + 4);
	else
		s = ft_strsub(s, idx + 4, len - idx - 4);
	free(ss);
	s = handle_round(s, precision, is_e ? idx : 0);
	len = ft_strlen(s);
	idx = ft_stridx(s, 'e');
	trailing_zeros(s, is_e ? idx : len, is_e);
	trailing_decimal(s);
	return (s);
}
