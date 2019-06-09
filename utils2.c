/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 22:08:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/09 14:59:53 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*read_lines(int fd)
{
	char	*res;
	char	*line;
	int		n;

	res = NULL;
	while ((n = get_next_line(fd, &line)) > 0)
	{
		if (n == 1)
		{
			if (res)
			{
				res = join_and_free(res, ft_strdup("\n"));
				res = join_and_free(res, line);
			}
			else
				res = join_and_free(line, ft_strdup("\n"));
		}
		else
			res = join_and_free(res, line);
	}
	return (res);
}

char	*read_file(char *fpath, char *algo)
{
	char	*res;
	int		fd;

	res = NULL;
	if ((fd = open(fpath, O_RDONLY)) > 0)
	{
		res = read_lines(fd);
		close(fd);
	}
	else
		no_such_file(fpath, algo);
	return (res);
}

char	*read_stdin(void)
{
	return (read_lines(STDIN_FILENO));
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
		"Message Digest commands:\nmd5\nsha256\n", cmd);
	return (0);
}

void	illegal_option(char *algo, char *option)
{
	ft_printf("%s: illegal option -- %s\n", algo, option);
	usage();
}

void	no_such_file(char *fpath, char *algo)
{
	ft_printf("ft_ssl: %s: %s: No such file or directory\n", algo, fpath);
}

void	s_flag_error(char *algo)
{
	ft_printf("%s: option requires an argument -- s", algo);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]", algo);
}
