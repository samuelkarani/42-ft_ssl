/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 23:46:45 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/04 17:10:53 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_base(int n, int base, int fd)
{
	int mod;

	if (n < 0)
	{
		if (base == 10)
			ft_putchar_fd('-', fd);
		if (ft_abs(n / base) > 0)
			ft_putnbr_base(ft_abs(n / base), base, fd);
	}
	if (n >= base)
		ft_putnbr_base(n / base, base, fd);
	mod = ft_abs(n % base);
	ft_putchar_fd(mod < 10 ? mod + '0' : mod - 10 + 'a', fd);
}
