/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:50:49 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/13 21:55:54 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*apply_width(char *s, int min_width)
{
	int		len;
	char	*tmp;

	tmp = s;
	len = ft_strlen(s);
	if (len < min_width)
	{
		s = ft_strnewpad(min_width, ' ');
		ft_memcpy(s + min_width - len, tmp, len);
		free(tmp);
	}
	return (s);
}
