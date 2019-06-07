/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:04:52 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/16 00:28:20 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*apply_space(char *s, int specifier, int min_width)
{
	char *tmp;

	if ((specifier == D || specifier == I || specifier == F)
		&& (check_neg(s) == -1 && s[0] != ' '))
	{
		if (min_width != -1 && s[0] == '0')
			s[0] = ' ';
		else
		{
			tmp = s;
			s = ft_strjoin(" ", s);
			free(tmp);
		}
	}
	return (s);
}

char	*apply_zero(char *s, int specifier, int precision, int min_width)
{
	int i;

	i = 0;
	if (!(precision != -1 && specifier >= D && specifier <= XX)
		&& min_width != -1)
	{
		i = 0;
		while (s[i] == ' ')
		{
			if (i == 0 && check_neg(s) >= 0)
				s[i] = '-';
			else
				s[i] = '0';
			i++;
		}
		if (i && s[i] == '-')
			s[i] = '0';
	}
	return (s);
}

char	*apply_minus(char *s)
{
	int i;
	int len;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (i)
	{
		len = ft_strlen(s);
		ft_memmove(s, s + i, len - i);
		i = len - i;
		while (i < len)
			s[i++] = ' ';
	}
	return (s);
}

char	*apply_flags(char *s, int *flags, int *info)
{
	if (flags[ZERO] && !flags[MINUS])
		s = apply_zero(s, info[SPCFR], info[PRCSN], info[MNWDTH]);
	if (flags[HASH])
		s = apply_hash(s, info[SPCFR], info[PRCSN], info[BSE]);
	if (flags[PLUS] && flags[SPACE])
		s = apply_plus(s, info[SPCFR], info[MNWDTH], info[BSE]);
	if (flags[PLUS] && !flags[SPACE])
		s = apply_plus(s, info[SPCFR], info[MNWDTH], info[BSE]);
	if (flags[SPACE] && !flags[PLUS])
		s = apply_space(s, info[SPCFR], info[MNWDTH]);
	if (flags[ZERO] && flags[MINUS])
		s = apply_minus(s);
	if (flags[MINUS] && !flags[ZERO])
		s = apply_minus(s);
	if (flags[APOSTROPHE])
		s = apply_apostrophe(s, info[SPCFR]);
	return (s);
}
