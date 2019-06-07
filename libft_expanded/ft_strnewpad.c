/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnewpad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:38:51 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/17 15:39:05 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnewpad(size_t n, char c)
{
	char *ret;

	ret = ft_strnew(n);
	return (ft_memset(ret, c, n));
}
