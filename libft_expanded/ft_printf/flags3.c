/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:20:14 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/13 20:33:29 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*prefix_helper(char *s, char *prefix, unsigned int i)
{
	char	*tmp;
	int		plen;
	int		slen;

	s = s + i;
	tmp = s;
	slen = ft_strlen(s);
	plen = ft_strlen(prefix);
	s = ft_strnew(slen + plen);
	ft_memcpy(s, prefix, plen);
	ft_memcpy(s + plen, tmp, slen);
	free(tmp - i);
	return (s);
}

char		*join_prefix(char *s, char *prefix)
{
	char *tmp;

	tmp = s;
	s = ft_strjoin(prefix, s);
	free(tmp);
	return (s);
}

static char	*prefix_zero(char *s, char *prefix, int plen)
{
	int i;

	i = 0;
	while (s[i] == '0' && s[i + 1] == '0')
	{
		if (i == plen)
			break ;
		i++;
	}
	if (i)
	{
		if (i == plen)
			ft_strncpy(s, prefix, plen);
		else
			s = prefix_helper(s, prefix, i);
	}
	else
		s = join_prefix(s, prefix);
	return (s);
}

char		*apply_prefix(char *s, char *prefix)
{
	int	plen;
	int i;

	plen = ft_strlen(prefix);
	i = 0;
	while (s[i] == ' ')
		i++;
	if (i)
		if (i - plen >= 0)
			ft_strncpy(s + i - plen, prefix, plen);
		else
			s = prefix_helper(s, prefix, i);
	else
		s = prefix_zero(s, prefix, plen);
	return (s);
}
