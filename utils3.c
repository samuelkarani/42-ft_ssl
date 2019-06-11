/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 21:58:50 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/10 22:09:01 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			valid_command(char *s)
{
	return (ft_strequ(s, "md5") || ft_strequ(s, "sha256"));
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

void		join_print(uint8_t *digest, char *algo, int newline)
{
	uint32_t	*sha256;
	int			i;

	i = 0;
	if (ft_strequ(algo, "MD5") || ft_strequ(algo, "md5"))
	{
		while (i < 16)
			ft_printf("%02x", digest[i++]);
	}
	else
	{
		sha256 = (uint32_t *)digest;
		while (i < 8)
			ft_printf("%.8x", sha256[i++]);
	}
	if (newline)
		ft_putchar('\n');
}

uint64_t	ft_strlen_llu(uint8_t *s)
{
	uint64_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}
