/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 21:59:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/10 22:08:31 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		usage(void)
{
	ft_putendl("usage: ft_ssl command [command opts] [command args]");
	return (0);
}

int		invalid_command(char *cmd)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n"
		"Message Digest commands:\nmd5\nsha256\n", cmd);
	return (0);
}

void	illegal_option(char *algo, char *option)
{
	ft_printf("%s: illegal option -- %s\n", algo, option);
	usage();
}

void	*no_file(char *fpath, char *algo)
{
	ft_printf("ft_ssl: %s: %s: No such file or directory\n", algo, fpath);
	return (NULL);
}

void	*s_flag_error(char *algo)
{
	ft_printf("%s: option requires an argument -- s", algo);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]", algo);
	return (NULL);
}
