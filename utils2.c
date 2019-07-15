/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 22:08:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/14 18:11:41 by smbaabu          ###   ########.fr       */
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
	if (!res && n == 0)
		res = ft_strdup("");
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
		no_file(fpath, algo);
	return (res);
}

char	*read_stdin(void)
{
	return (read_lines(STDIN_FILENO));
}
