/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:43:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/10 22:04:09 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	lr(uint32_t n, uint32_t s)
{
	return ((n << s) | (n >> (32 - s)));
}

uint32_t	rr(uint32_t n, uint32_t s)
{
	return ((n >> s) | (n << (32 - s)));
}

uint64_t	get_bytes(uint64_t n)
{
	if (n % 8 != 0)
		return (n + (8 - n % 8));
	return (n);
}

uint32_t	swap_int32(const uint32_t value)
{
	uint32_t result;

	result = 0;
	result |= (value & 0x000000FF) << 24;
	result |= (value & 0x0000FF00) << 8;
	result |= (value & 0x00FF0000) >> 8;
	result |= (value & 0xFF000000) >> 24;
	return (result);
}

uint32_t	*swap_arr32(uint32_t *values, size_t bytes)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = bytes / sizeof(uint32_t);
	while (i < n)
	{
		values[i] = swap_int32(values[i]);
		i++;
	}
	return (values);
}
