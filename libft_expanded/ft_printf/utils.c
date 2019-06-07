/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 22:15:36 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/17 15:39:38 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*create_str(char c, int *nul_count)
{
	char *ret;

	ret = ft_strnew(1);
	if (c)
		ret[0] = c;
	else
	{
		ret[0] = MAGIC_CHR;
		(*nul_count)++;
	}
	return (ret);
}

void	pre_print(char **s, int nul_count)
{
	char	*handle;
	int		i;

	handle = *s;
	if (handle == NULL)
		handle = NULL_PRINT;
	else
	{
		i = 0;
		while (handle[i] && nul_count > 0)
		{
			if (handle[i] == MAGIC_CHR)
			{
				handle[i] = '\x00';
				nul_count--;
			}
			i++;
		}
	}
}

char	*strdup_wrapper(const char *s1)
{
	if (s1 == NULL)
		return (ft_strdup(NULL_PRINT));
	return (ft_strdup(s1));
}

size_t	getlen(long long n, int base)
{
	int i;

	if (n == 0)
		return (1);
	i = 1;
	while (n /= base)
		i++;
	return (i);
}
