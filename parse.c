/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 20:35:51 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/10 21:19:18 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		parse_flags(char **av, int *flags, t_ssl *args, int *iidx)
{
	int		done;
	int		i;
	int		idx;

	done = 0;
	i = iidx[0];
	idx = iidx[1];
	if (ft_strequ(av[i], "-p") && (flags[0] = 1))
		args[idx++] = (t_ssl){NULL, 0, 0};
	else if (ft_strequ(av[i], "-q"))
		flags[1] = 1;
	else if (ft_strequ(av[i], "-r"))
		flags[2] = 1;
	else if (ft_strequ(av[i], "-s") && (flags[3] = 1))
		args[idx++] = av[++i] ? (t_ssl){av[i], 2, 0} : (t_ssl){NULL, 2, 1};
	else
	{
		done = 1;
		args[idx++] = av[i][0] == '-' && av[i][1]
			? (t_ssl){av[i], -1, 1} : (t_ssl){av[i], 1, 0};
	}
	iidx[0] = i;
	iidx[1] = idx;
	return (done);
}

int		parse(char **av, int *flags, t_ssl *args)
{
	int		iidx[2];
	int		done;

	done = 0;
	iidx[0] = 2;
	iidx[1] = 0;
	while (av[iidx[0]] && iidx[0] < 256)
	{
		if (!done)
			done = parse_flags(av, flags, args, iidx);
		else
			args[iidx[1]++] = (t_ssl){av[iidx[0]], 1, 0};
		iidx[0]++;
	}
	if (!iidx[1])
		args[iidx[1]++] = (t_ssl){NULL, 0, 0};
	return (iidx[1]);
}
