/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:43:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/08 14:11:45 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	ft_strlen_llu(uint8_t *s)
{
	uint64_t count;

	count = 0;
	while (*s++)
		count++;
	return count;
}

uint32_t	len_llu(uint64_t n, uint64_t base)
{
	uint32_t i;

	if (n == 0)
		return (1);
	i = 1;
	while (n /= base)
		i++;
	return (i);
}

uint8_t	*ft_itoa_base_llu(uint64_t n, uint32_t base)
{
	uint8_t		*ret;
	size_t		len;
	uint64_t	mod;

	if (base < 2 || base > 16)
		return (NULL);
	len = len_llu(n, base);
	ret = ft_memalloc(len + 1);
	if (n == 0)
		ret[0] = '0';
	while (n)
	{
		mod = n % base;
		ret[--len] = mod < 10 ? mod + '0' : mod - 10 + 'a';
		n = n / base;
	}
	return (ret);
}

uint8_t	*ft_itoa_llu(uint64_t n)
{
	return (ft_itoa_base_llu(n, 10));
}

uint32_t *ft_memcpy_ints(uint32_t *dst, uint32_t *src, int n)
{
	uint32_t	i;

	i = 0;
	while (i++ < n)
		*dst++ = *src++;
	return (dst);
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

void	print_binary_char(uint8_t *message, uint64_t mlen)
{
	uint64_t	i;

	i = 0;
	while (i < mlen)
	{
		print_bit(message[i++]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

void	print_binary_ints(uint32_t *arr, uint32_t len)
{
	uint32_t	i;

	i = 0;
	while (i < len)
	{
		print_bit(arr[i++]);
		ft_putchar(' ');
	}
	ft_putchar(' ');
}

void	print_hex_ints(uint32_t *arr, int n)
{
	uint32_t	i;

	i = 0;
	while (i < n)
		ft_printf("%#08x\n", arr[i++]);
}

void	join_print(uint8_t *vars)
{
	uint32_t	i;

	i = 0;
	while (i < 16)
		ft_printf("%02x", vars[i++]);
}
