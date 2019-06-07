/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:03:41 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/13 16:26:51 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*select_prefix(char *s, int specifier, int precision, int base)
{
	char *prefix;

	prefix = NULL;
	if (specifier == P && !(precision != -1 && s[0] == '0' && s[1]))
		prefix = "0x";
	if (precision != 0 && ft_strcmp(s, "0") != 0)
	{
		if (base == 8)
			prefix = "0";
		if (base == 16)
		{
			if (specifier == X)
				prefix = "0x";
			if (specifier == XX)
				prefix = "0X";
		}
	}
	return (prefix);
}

char		*apply_hash(char *s, int specifier, int precision, int base)
{
	char	*prefix;
	char	*tmp;

	if (specifier == F && precision == 0)
	{
		tmp = s;
		s = ft_strjoin(s, ".");
		free(tmp);
	}
	if (precision == 0 && base == 8)
	{
		free(s);
		s = ft_strdup("0");
	}
	if (specifier == P && (precision != -1 && s[0] == '0' && s[1]))
		s = join_prefix(s, "0x");
	if ((prefix = select_prefix(s, specifier, precision, base)))
		s = apply_prefix(s, prefix);
	return (s);
}

char		*apply_plus(char *s, int specifier, int min_width, int base)
{
	int	i;

	i = 0;
	if (base == 10 && (specifier == D || specifier == I || specifier == F)
		&& check_neg(s) == -1)
	{
		if (min_width != -1 && s[0] == '0')
			s[0] = '+';
		else
			s = apply_prefix(s, "+");
	}
	return (s);
}
