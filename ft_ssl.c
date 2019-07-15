/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:22:52 by smbaabu           #+#    #+#             */
/*   Updated: 2019/07/14 21:00:14 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	process(t_ssl arg, uint32_t *(*algorithm)(uint8_t *, uint64_t),
	int *flags, char *algo)
{
	char		*msg;
	uint32_t	*digest;

	msg = NULL;
	if (arg.type == -1)
		illegal_option(algo, arg.name);
	if (arg.type == 0)
	{
		msg = read_stdin();
		arg.name = ft_strdup(msg);
	}
	if (arg.type == 1)
		msg = arg.error ? no_file(arg.name, algo) : read_file(arg.name, algo);
	if (arg.type == 2)
		msg = arg.error ? s_flag_error(algo) : ft_strdup(arg.name);
	if (msg)
	{
		digest = (*algorithm)((uint8_t *)msg, ft_strlen_llu((uint8_t *)msg));
		print_digest(digest, arg, flags, algo);
		free(digest);
	}
}

void	dispatcher(char *algo, t_ssl *args, int no, int *flags)
{
	algo_f		*dispatch[2];
	int			i;
	int			idx;

	dispatch[0] = &md5;
	dispatch[1] = &sha256;
	idx = !ft_strequ("md5", algo);
	i = 0;
	while (i < no)
		process(args[i++], dispatch[idx], flags, algo);
}

int		main(int ac, char **av)
{
	int		flags[4];
	t_ssl	args[256];
	char	*algo;
	int		idx;

	if (ac > 1)
	{
		ft_bzero(flags, sizeof(flags));
		if (valid_command(av[1]))
		{
			algo = av[1];
			if ((idx = parse(av, flags, args)))
				dispatcher(algo, args, idx, flags);
		}
		else
			return (invalid_command(av[1]));
	}
	else
		return (usage());
}
