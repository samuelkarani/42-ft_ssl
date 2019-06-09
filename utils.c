/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:43:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/08 19:18:20 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	ft_strlen_llu(uint8_t *s)
{
	uint64_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

uint32_t	left_rotate(uint32_t n, uint32_t s)
{
	return ((n << s) | (n >> (32 - s)));
}

void		update(uint32_t *dst, uint32_t *src)
{
	int i;

	i = 0;
	while (i < 4)
	{
		dst[i] += src[i];
		i++;
	}
}

void		copy_round(uint32_t *vars)
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;

	a = vars[0];
	b = vars[1];
	c = vars[2];
	d = vars[3];
	vars[0] = d;
	vars[1] = a;
	vars[2] = b;
	vars[3] = c;
}

void		join_print(uint8_t *vars)
{
	int	i;

	i = 0;
	while (i < 16)
		ft_printf("%02x", vars[i++]);
}
