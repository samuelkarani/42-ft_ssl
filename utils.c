/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:43:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/08 18:36:14 by smbaabu          ###   ########.fr       */
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

void	join_print(uint8_t *vars)
{
	int	i;

	i = 0;
	while (i < 16)
		ft_printf("%02x", vars[i++]);
}
