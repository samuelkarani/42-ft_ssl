/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:16:05 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/08 19:20:09 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t	*append(uint8_t *message, uint64_t *mlen)
{
	uint8_t		*res;
	int			i;
	int			x;
	uint64_t	n;

	*mlen += 2;
	x = *mlen % 64;
	if (x > 56)
		i = 64 - (x - 56);
	else if (x < 56)
		i = 56 - x;
	else
		i = 64;
	res = ft_memalloc(*mlen + i + 8);
	ft_memcpy(res, message, *mlen - 2);
	res[*mlen - 2] = 10;
	res[*mlen - 1] = 128;
	ft_memset(res + *mlen, 0, i);
	n = (*mlen - 1) * 8;
	ft_memcpy(res + *mlen + i, &n, 8);
	*mlen = *mlen + i + 8;
	return (res);
}

void	compress(uint32_t *vars, size_t i, uint32_t *fg)
{
	uint32_t	f;
	uint32_t	g;

	if (i < 16)
	{
		f = (vars[1] & vars[2]) | (~vars[1] & vars[3]);
		g = i;
	}
	if (i >= 16 && i < 32)
	{
		f = (vars[3] & vars[1]) | (~vars[3] & vars[2]);
		g = (5 * i + 1) % 16;
	}
	if (i >= 32 && i < 48)
	{
		f = vars[1] ^ vars[2] ^ vars[3];
		g = (3 * i + 5) % 16;
	}
	if (i >= 48 && i < 64)
	{
		f = vars[2] ^ (vars[1] | ~vars[3]);
		g = (7 * i) % 16;
	}
	fg[0] = f;
	fg[1] = g;
}

void	md5(uint8_t *message, uint64_t mlen)
{
	uint32_t	cnts[4], vars[4], fg[2], i;
	uint64_t	j;

	message = append(message, &mlen);
	ft_memcpy(cnts, (uint32_t[]){0x67452301, 0xefcdab89, 0x98badcfe,
		0x10325476}, sizeof(cnts));
	j = 0;
	while (j < mlen)
	{
		ft_memcpy(vars, cnts, sizeof(vars));
		i = 0;
		while (i < 64)
		{
			compress(vars, i, fg);
			vars[0] = vars[1] + left_rotate(vars[0] + fg[0] + g_k[i] + ((uint32_t *)(message + j))[fg[1]], g_s[i]);
			copy_round(vars);
			i++;
		}
		update(cnts, vars);
		j += 64;
	}
	join_print((uint8_t *)cnts);
	free(message);
}

int		main(int ac, char **av)
{
	if (ac == 2)
		md5((uint8_t *)av[1], ft_strlen_llu((uint8_t *)av[1]));
}
