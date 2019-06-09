/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 18:36:31 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/08 18:44:07 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_byte(uint8_t o)
{
	int	i;

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

void	print_binary(uint8_t *message, size_t mlen)
{
	size_t	i;

	i = 0;
	while (i < mlen)
	{
		print_byte(message[i++]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

void	print_hex(uint32_t *arr, size_t n)
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
