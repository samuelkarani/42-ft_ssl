/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 22:08:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/09 12:34:39 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*read_file(char *fpath, char *algo)
{
	char	*res;
	char	*line;
	int		fd;

	res = NULL;
	if ((fd = open(fpath, O_RDONLY)))
	{
		while (get_next_line(fd, &line))
			res = join_and_free(res, line);
		close(fd);
	}
	else
		no_such_file(fpath, algo);
	return (res);
}

char	*read_stdin(void)
{
	char	*res;
	char	*line;

	res = NULL;
	while (get_next_line(STDIN_FILENO, &line))
		res = join_and_free(res, line);
	return (res);
}

int	valid_command(char *s)
{
	return (ft_strequ(s, "md5") || ft_strequ(s, "sha256"));
}

int	usage(void)
{
	ft_putendl("usage: ft_ssl command [command opts] [command args]");
	return (0);
}

int	invalid_command(char *cmd)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n"
		"Message Digest commands:\nmd5\nsha256", cmd);
	return (0);
}

int	illegal_option(char *algo, char *option)
{
	ft_printf("%s: illegal option -- %s\n", algo, option);
	usage();
	return (1);
}

int	no_such_file(char *fpath, char *algo)
{
	ft_printf("ft_ssl: %s: %s: No such file or directory", algo, fpath);
	return (1);
}

int	s_flag_error(char *algo)
{
	ft_printf("%s: option requires an argument -- s", algo);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]", algo);
	return (1);
}
