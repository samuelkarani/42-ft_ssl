/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:04:32 by smbaabu           #+#    #+#             */
/*   Updated: 2019/02/26 18:37:25 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int			ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 32);
	return (c);
}