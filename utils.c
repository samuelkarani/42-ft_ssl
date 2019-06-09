/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:43:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/09 13:32:45 by smbaabu          ###   ########.fr       */
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

uint32_t	right_rotate(uint32_t n, uint32_t s)
{
	return ((n >> s) | (n << (32 - s)));
}

void		update(uint32_t *dst, uint32_t *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		dst[i] += src[i];
		i++;
	}
}

void		join_print(uint8_t *vars, int newline)
{
	int	i;

	i = 0;
	while (i < 16)
		ft_printf("%02x", vars[i++]);
	if (newline)
		ft_putchar('\n');
}

uint64_t		swap_int64(const uint64_t val)
{
	return ((((val) & 0xff00000000000000ull) >> 56) |
			(((val) & 0x00ff000000000000ull) >> 40) |
			(((val) & 0x0000ff0000000000ull) >> 24) |
			(((val) & 0x000000ff00000000ull) >> 8) |
			(((val) & 0x00000000ff000000ull) << 8) |
			(((val) & 0x0000000000ff0000ull) << 24) |
			(((val) & 0x000000000000ff00ull) << 40) |
			(((val) & 0x00000000000000ffull) << 56));
}

uint64_t	*swap(uint64_t *values, size_t n)
{
	size_t i;

	i = 0;
	while (i < n / sizeof(uint64_t))
		swap_int64(values[i++]);
	return (values);
}
