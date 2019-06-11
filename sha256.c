/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 20:10:04 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/10 20:08:10 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	get_bytes(uint64_t n)
{
	if (n % 8 != 0)
		return (n + (8 - n % 8));
	return (n);
}

uint8_t		*append_free_sha(uint8_t *message, uint64_t *mlen)
{
	uint8_t	*res;
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

void		copy_round_sha(uint32_t *vars, uint32_t tmp1, uint32_t tmp2)
{
	vars[7] = vars[6];
	vars[6] = vars[5];
	vars[5] = vars[4];
	vars[4] = vars[3] + tmp1;
	vars[3] = vars[2];
	vars[2] = vars[1];
	vars[1] = vars[0];
	vars[0] = tmp1 + tmp2;
}

uint32_t	*sha256(uint8_t *message, uint64_t mlen)
{
	uint32_t	*w;
	uint32_t	vars[8];
	uint32_t	tmps[8];
	uint32_t	*digest;
	uint64_t	j;
	int			i;
	
	message = append_free_sha(message, &mlen);
	digest = malloc(sizeof(uint32_t) * 8);
	ft_memcpy(digest, (uint32_t[]){0x6a09e667, 0xbb67ae85, 0x3c6ef372,
		0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19},
		8 * sizeof(uint32_t));
	j = 0;
	while (j < mlen)
	{
		w = malloc(64 * sizeof(uint32_t));
		ft_memcpy(w, message + j, 16 * sizeof(uint32_t));
		i = 16;
		while (i < 64)
		{
			tmps[0] = right_rotate(w[i - 15], 7) ^ right_rotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
			tmps[1] = right_rotate(w[i - 2], 17) ^ right_rotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
			w[i] = w[i - 16] + tmps[0] + w[i - 7] + tmps[1];
			i++;
		}
		ft_memcpy(vars, digest, sizeof(vars));
		i = 0;
		while (i < 64)
		{
			tmps[1] = right_rotate(vars[4], 6) ^ right_rotate(vars[4], 11) ^ right_rotate(vars[4], 25);
			tmps[2] = (vars[4] & vars[5]) ^ (~vars[4] & vars[6]);
			tmps[3] = vars[7] + tmps[1] + tmps[2] + g_sha256_k[i] + w[i];
			tmps[0] = right_rotate(vars[0], 2) ^ right_rotate(vars[0], 13) ^ right_rotate(vars[0], 22);
			tmps[5] = (vars[0] & vars[1]) ^ (vars[0] & vars[2]) ^ (vars[1] & vars[2]);
			tmps[4] = tmps[0] + tmps[5];
			copy_round_sha(vars, tmps[3], tmps[4]);
			i++;
		}
		update(digest, vars, 8);
		free(w);
		j += 64;
	}
	free(message);
	return ((uint32_t *)digest);
}
