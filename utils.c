/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:43:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/08 16:25:49 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	ft_strlen_llu(uint8_t *s)
{
	uint64_t	count;

	count = 0;
	while (*s++)
		count++;
	return count;
}

void	print_bit(uint8_t o)
{
	uint32_t	i;

	i = 0;
	while (i < 8)
	{
		if (o & (1 << (7 - i)))
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i++;
	}
}

void	print_binary_char(uint8_t *message, size_t mlen)
{
	size_t	i;

	i = 0;
	while (i < mlen)
	{
		print_bit(message[i++]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

void	print_binary_ints(uint32_t *arr, size_t len)
{
	uint32_t	i;

	i = 0;
	while (i < len)
	{
		print_bit(arr[i++]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

void	print_hex_ints(uint32_t *arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ft_printf("%#08x", arr[i++]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
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

void	join_print(uint32_t *vars)
{
	int			i;

	i = -1;
	while (++i < 4)
		ft_printf("%8.8x", swap_int32(vars[i]));
}
