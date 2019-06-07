/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 22:18:42 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/12 16:30:20 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_validity(const char *s, int start)
{
	int i;
	int j;
	int idx;

	i = start;
	while (s[i])
	{
		if ((idx = ft_stridx(SPECIFIERS, s[i])) >= 0)
		{
			idx = ft_stridx(s, SPECIFIERS[idx]);
			j = start;
			while (j < idx)
			{
				if (!(ft_stridx(NON_SPECIFIERS, s[j]) >= 0 || ft_isdigit(s[j])))
					return (-1);
				j++;
			}
			return (1);
		}
		i++;
	}
	return (-1);
}

int			check_specifier(const char *s, int start, int *upto)
{
	int		i;
	int		idx;

	i = start;
	while (s[i])
	{
		if ((idx = ft_stridx(SPECIFIERS, s[i])) != -1)
		{
			*upto = i;
			return (idx);
		}
		i++;
	}
	return (-1);
}

static int	check_hh(const char *s)
{
	if (*s == 'h' && *(s + 1) == 'h')
		return (1);
	if (*s == 'h')
		return (2);
	return (0);
}

static int	check_ll(const char *s)
{
	if (*s == 'l' && *(s + 1) == 'l')
		return (4);
	if (*s == 'l')
		return (3);
	if (*s == 'L')
		return (5);
	return (0);
}

int			check_modifier(const char *s, int start, int *upto)
{
	int	i;
	int idx;

	idx = 0;
	i = start;
	while (i < *upto)
	{
		if ((idx = check_ll(s + i) + check_hh(s + i)))
		{
			*upto = i;
			return (idx);
		}
		i++;
	}
	return (-1);
}
