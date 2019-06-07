/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:53:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/15 15:13:31 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*handle_carry(char *ret, int i)
{
	int carry;

	carry = 0;
	while (i >= 0)
	{
		if (ret[i + 1] >= '5')
		{
			if (carry)
				ret[i + 1] = '0';
			if (ret[i] == '.')
				i--;
			if ((ret[i] += 1) > '9')
			{
				i--;
				carry = 1;
			}
			else
				break ;
		}
		else
			break ;
	}
	return (ret);
}

char		*round_up(char *num, int precision)
{
	char	*ret;
	char	*tmp;
	int		len;
	int		i;
	int		idx;

	ret = ft_strdup(num);
	idx = ft_stridx(ret, '.');
	i = idx + precision;
	tmp = handle_carry(ret, i);
	len = idx + precision + 1;
	if (i < 0)
	{
		ret[0] = '0';
		ret = ft_strnew(len + 1);
		ft_strncpy(ret + 1, tmp, len);
		ret[0] = '1';
		free(tmp);
		return (ret);
	}
	ret = ft_strncpy(ft_strnew(len), ret, len);
	free(tmp);
	return (ret);
}
