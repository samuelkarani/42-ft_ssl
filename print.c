/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:50:22 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/10 22:06:36 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_stdin(uint32_t *digest, t_ssl arg, int *flags, char *algo)
{
	if (flags[0])
	{
		ft_putstr(arg.name);
		free(arg.name);
	}
	join_print((uint8_t *)digest, algo, 1);
}

void	print_file(uint32_t *digest, t_ssl arg, int *flags, char *algo)
{
	if (flags[2])
	{
		join_print((uint8_t *)digest, algo, flags[1] ? 1 : 0);
		if (!flags[1])
			ft_printf(" %s\n", arg.name);
	}
	else
	{
		if (!flags[1])
			ft_printf("%s (%s) = ", ft_strupper(algo), arg.name);
		join_print((uint8_t *)digest, algo, 1);
	}
}

void	print_string(uint32_t *digest, t_ssl arg, int *flags, char *algo)
{
	if (flags[2])
	{
		join_print((uint8_t *)digest, algo, flags[1] ? 1 : 0);
		if (!flags[1])
			ft_printf(" \"%s\"\n", arg.name);
	}
	else
	{
		if (!flags[1])
			ft_printf("%s (\"%s\") = ", ft_strupper(algo), arg.name);
		join_print((uint8_t *)digest, algo, 1);
	}
}

void	print_digest(uint32_t *digest, t_ssl arg, int *flags, char *algo)
{
	if (arg.type == 0)
		print_stdin(digest, arg, flags, algo);
	if (arg.type == 1)
		print_file(digest, arg, flags, algo);
	if (arg.type == 2)
		print_string(digest, arg, flags, algo);
}
