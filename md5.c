/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:16:05 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/10 20:13:21 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t		*append_free_md5(uint8_t *message, uint64_t *mlen)
{
	uint8_t		*res;
	int			i;
	int			x;
	uint64_t	n;

	*mlen += 1;
	x = *mlen % 64;
	if (x > 56)
		i = 64 - (x - 56);
	else if (x < 56)
		i = 56 - x;
	else
		i = 64;
	res = malloc(*mlen + i + 8);
	ft_memcpy(res, message, *mlen - 1);
	res[*mlen - 1] = 128;
	ft_memset(res + *mlen, 0, i);
	n = (*mlen - 1) * 8;
	ft_memcpy(res + *mlen + i, &n, 8);
	*mlen = *mlen + i + 8;
	free(message);
	return (res);
}

void		compress_md5(uint32_t *vars, size_t i, uint32_t *fg)
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

void		copy_round_md5(uint32_t *vars)
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

uint32_t	*md5(uint8_t *message, uint64_t mlen)
{
	uint32_t	vars[4], fg[2], i;
	uint32_t	*digest;
	uint64_t	j;

	message = append_free_md5(message, &mlen);
	digest = malloc(sizeof(vars));
	ft_memcpy(digest, (uint32_t[]){0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476}, sizeof(vars));
	j = 0;
	while (j < mlen)
	{
		ft_memcpy(vars, digest, sizeof(vars));
		i = 0;
		while (i < 64)
		{
			compress_md5(vars, i, fg);
			vars[0] = vars[1] + left_rotate(vars[0] + fg[0] + g_md5_k[i] + ((uint32_t *)(message + j))[fg[1]], g_md5_s[i]);
			copy_round_md5(vars);
			i++;
		}
		update(digest, vars, 4);
		j += 64;
	}
	free(message);
	return (digest);
}
