/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:29:19 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/13 17:34:31 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		*create_flags(int n)
{
	int *ret;
	int i;

	ret = (int *)malloc(n * sizeof(int));
	i = 0;
	while (i < n)
		ret[i++] = 0;
	return (ret);
}

void	clear_flags(int *flags, int n)
{
	int i;

	i = 0;
	while (i < n)
		flags[i++] = 0;
}

int		atleast_one(int *flags, int n)
{
	int i;

	i = 0;
	while (i < n)
		if (flags[i++] == 1)
			return (1);
	return (-1);
}

int		**create_info(int *info[], int n)
{
	int	i;

	i = 0;
	while (i < n)
		info[i++] = (int *)malloc(sizeof(int));
	return (info);
}

void	destroy_info(int *info[], int n)
{
	int i;

	i = 0;
	while (i < n)
		free(info[i++]);
}
