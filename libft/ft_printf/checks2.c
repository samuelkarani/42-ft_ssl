/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:37:08 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/13 16:39:03 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	update(const char *s, int a, int b)
{
	char	*num;
	int		ret;

	num = ft_strsub(s, a, b);
	ret = ft_atoi(num);
	free(num);
	return (ret);
}

int			check_precision(const char *s, int start, int *upto)
{
	int		i;
	int		j;
	int		ret;

	i = start;
	while (i < *upto)
	{
		if (s[i] == '.')
		{
			*upto = i;
			j = i + 1;
			while (ft_isdigit(s[j]))
				j++;
			if (j > i + 1)
			{
				ret = update(s, i + 1, j - i - 1);
				return (ret < 0 ? -1 : ret);
			}
			return (0);
		}
		i++;
	}
	return (-1);
}

int			check_width(const char *s, int start, int *upto)
{
	int		i;
	int		j;
	int		ret;

	i = start;
	while (i < *upto && s[i] != '.')
	{
		if (s[i] == '0')
		{
			i++;
			continue ;
		}
		j = i;
		while (ft_isdigit(s[j]) && s[j] != '.')
			j++;
		if (j - i)
		{
			*upto = i;
			ret = update(s, i, j - i);
			return (ret);
		}
		i++;
	}
	return (-1);
}

void		check_flags(const char *s, int start, int upto, int *flags)
{
	int	i;
	int	idx;

	i = start;
	while (i < upto)
	{
		if ((idx = ft_stridx(FLAGS, s[i])) != -1)
			flags[idx] = 1;
		i++;
	}
}
