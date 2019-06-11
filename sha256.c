/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 20:10:04 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/10 22:32:36 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t		*append_free_sha(uint8_t *message, uint64_t *mlen)
{
	uint8_t		*res;
	int			i;
	int			x;
	uint32_t	n;

	*mlen += 1;
	x = *mlen % 64;
	if (x > 60)
		i = 64 - (x - 60);
	else if (x < 60)
		i = 60 - x;
	else
		i = 0;
	res = ft_memalloc(*mlen + i + 4);
	ft_memcpy(res, message, *mlen - 1);
	res[*mlen - 1] = 128;
	swap_arr32((uint32_t *)res, get_bytes(*mlen));
	n = (*mlen - 1) * 8;
	ft_memcpy(res + *mlen + i, &n, 4);
	*mlen = *mlen + i + 4;
	free(message);
	return (res);
}

void		copy_round_sha(uint32_t *vrs, uint32_t tmp1, uint32_t tmp2)
{
	vrs[7] = vrs[6];
	vrs[6] = vrs[5];
	vrs[5] = vrs[4];
	vrs[4] = vrs[3] + tmp1;
	vrs[3] = vrs[2];
	vrs[2] = vrs[1];
	vrs[1] = vrs[0];
	vrs[0] = tmp1 + tmp2;
}

void		calc_sha(uint32_t *tmp, uint32_t *vrs, uint32_t *w, int i)
{
	tmp[1] = rr(vrs[4], 6) ^ rr(vrs[4], 11) ^ rr(vrs[4], 25);
	tmp[2] = (vrs[4] & vrs[5]) ^ (~vrs[4] & vrs[6]);
	tmp[3] = vrs[7] + tmp[1] + tmp[2] + g_sha256_k[i] + w[i];
	tmp[0] = rr(vrs[0], 2) ^ rr(vrs[0], 13) ^ rr(vrs[0], 22);
	tmp[5] = (vrs[0] & vrs[1]) ^ (vrs[0] & vrs[2]) ^ (vrs[1] & vrs[2]);
	tmp[4] = tmp[0] + tmp[5];
}

void		compress_sha(uint8_t *message, uint32_t *digest)
{
	uint32_t	*w;
	int			i;
	uint32_t	vrs[8];
	uint32_t	tmp[8];

	w = malloc(64 * sizeof(uint32_t));
	ft_memcpy(w, message, 16 * sizeof(uint32_t));
	i = 16;
	while (i < 64)
	{
		tmp[0] = rr(w[i - 15], 7) ^ rr(w[i - 15], 18) ^ (w[i - 15] >> 3);
		tmp[1] = rr(w[i - 2], 17) ^ rr(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + tmp[0] + w[i - 7] + tmp[1];
		i++;
	}
	ft_memcpy(vrs, digest, sizeof(vrs));
	i = 0;
	while (i < 64)
	{
		calc_sha(tmp, vrs, w, i);
		copy_round_sha(vrs, tmp[3], tmp[4]);
		i++;
	}
	update(digest, vrs, 8);
	free(w);
}

uint32_t	*sha256(uint8_t *message, uint64_t mlen)
{
	uint32_t	*digest;
	uint64_t	j;

	message = append_free_sha(message, &mlen);
	digest = malloc(sizeof(uint32_t) * 8);
	ft_memcpy(digest, g_init_sha256, 8 * sizeof(uint32_t));
	j = 0;
	while (j < mlen)
	{
		compress_sha(message + j, digest);
		j += 64;
	}
	free(message);
	return ((uint32_t *)digest);
}
