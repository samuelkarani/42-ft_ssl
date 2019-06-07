/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 22:41:32 by smbaabu           #+#    #+#             */
/*   Updated: 2019/03/18 16:49:35 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strjoin_custom(char **line, char *s2)
{
	char	*temp;

	temp = *line;
	*line = ft_strjoin(*line, s2);
	if (temp)
		free(temp);
}

int		ft_checknewline(char **line, char **line_ptrs, char *buf, int prev)
{
	char	*temp;

	if ((*line_ptrs = ft_strchr(buf ? buf : *line, '\n')))
	{
		if (prev)
		{
			temp = *line;
			*line = ft_strsub(*line, 0, *line_ptrs - *line);
		}
		else
		{
			temp = ft_strsub(buf, 0, *line_ptrs - buf);
			ft_strjoin_custom(line, temp);
		}
		*line_ptrs = *(*line_ptrs + 1) ? ft_strdup(++*line_ptrs) : NULL;
		free(temp);
		return (1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int			n;
	char		buf[BUFF_SIZE + 1];
	static char *line_ptrs[NUM_FD];

	if (fd < 0 || fd > NUM_FD - 1 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	*line = line_ptrs[fd];
	if (*line && ft_checknewline(line, &line_ptrs[fd], NULL, 1))
		return (1);
	n = 0;
	while ((n = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[n] = 0;
		if (ft_checknewline(line, &line_ptrs[fd], buf, 0))
			return (1);
		ft_strjoin_custom(line, buf);
	}
	if (*line && n != -1)
	{
		line_ptrs[fd] = NULL;
		return (1);
	}
	return (n);
}
