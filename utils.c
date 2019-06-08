/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:43:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/07 22:40:08 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned long long	ft_strlen_llu(char *s)
{
	unsigned long long count;

	count = 0;
	while (*s++)
		count++;
	return count;
}

int		len_llu(unsigned long long n)
{
	int i;

	if (n == 0)
		return (1);
	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char	*ft_itoa_llu(unsigned long long n)
{
	char	*ret;
	int		len;

	len = len_llu(n);
	ret = ft_memalloc(len + 1);
	if (n == 0)
		ret[0] = '0';
	while (n)
	{
		ret[--len] = ft_abs(n % 10) + '0';
		n = n / 10;
	}
	return (ret);
}

unsigned int *ft_memcpy_ints(unsigned int *dst, unsigned int *src, int n)
{
	int	i;

	i = 0;
	while (i++ < n)
		*dst++ = *src++;
	return (dst);
}

void	print_bit(unsigned char o)
{
	int i;

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

void	print_binary(char *message, unsigned long long mlen)
{
	unsigned long long	i;

	i = 0;
	while (i < mlen)
	{
		print_bit(message[i++]);
		ft_putchar('\n');
	}
}

void	print_hex(unsigned int *arr, int n)
{
	int i;

	i = 0;
	while (i < n)
		ft_printf("%#x\n", arr[i++]);
}

void	join_print(unsigned char *vars)
{
	int i;

	i = 0;
	while (i < 16)
		ft_printf("%02x", vars[i++]);
}
