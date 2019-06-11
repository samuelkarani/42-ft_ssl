/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 22:08:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/10 20:21:01 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*ft_strupper(char *s)
{
	char	*res;

	res = s;
	while (*s)
	{
		if (ft_islower(*s))
			*s -= 32;
		s++;
	}
	return (res);
}

char	*read_lines(int fd)
{
	int		n;
	char	*buf;
	char	*res;
	char	*tmp;

	res = NULL;
	n = 65535;
	buf = malloc(n * sizeof(char));
	while ((n = read(fd, buf, n)) > 0)
	{
		buf[n] = 0;
		tmp = res;
		res = ft_strjoin(res, buf);
		free(tmp);
	}
	free(buf);
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
