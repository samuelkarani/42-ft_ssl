/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:16:05 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/10 21:54:09 by smbaabu          ###   ########.fr       */
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

void		compress_md5(uint32_t *vrs, size_t i, uint32_t *fg)
{
	uint32_t	f;
	uint32_t	g;

	if (i < 16)
	{
		f = (vrs[1] & vrs[2]) | (~vrs[1] & vrs[3]);
		g = i;
	}
	if (i >= 16 && i < 32)
	{
		f = (vrs[3] & vrs[1]) | (~vrs[3] & vrs[2]);
		g = (5 * i + 1) % 16;
	}
	if (i >= 32 && i < 48)
	{
		f = vrs[1] ^ vrs[2] ^ vrs[3];
		g = (3 * i + 5) % 16;
	}
	if (i >= 48 && i < 64)
	{
		f = vrs[2] ^ (vrs[1] | ~vrs[3]);
		g = (7 * i) % 16;
	}
	fg[0] = f;
	fg[1] = g;
}

void		copy_round_md5(uint32_t *vrs)
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;

	a = vrs[0];
	b = vrs[1];
	c = vrs[2];
	d = vrs[3];
	vrs[0] = d;
	vrs[1] = a;
	vrs[2] = b;
	vrs[3] = c;
}

void		calc_md5(uint32_t message, uint32_t *vrs, uint32_t *fg, int i)
{
	uint32_t	res;

	res = lr(vrs[0] + fg[0] + g_md5_k[i] + message, g_md5_s[i]);
	vrs[0] = vrs[1] + res;
}

uint32_t	*md5(uint8_t *message, uint64_t mlen)
{
	uint32_t	vrs[4];
	uint32_t	fg[2];
	uint32_t	i;
	uint32_t	*digest;
	uint64_t	j;

	message = append_free_md5(message, &mlen);
	digest = malloc(sizeof(vrs));
	ft_memcpy(digest, g_init_md5, sizeof(vrs));
	j = 0;
	while (j < mlen)
	{
		ft_memcpy(vrs, digest, sizeof(vrs));
		i = -1;
		while (++i < 64)
		{
			compress_md5(vrs, i, fg);
			calc_md5(((uint32_t *)(message + j))[fg[1]], vrs, fg, i);
			copy_round_md5(vrs);
		}
		update(digest, vrs, 4);
		j += 64;
	}
	free(message);
	return (digest);
}
