/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:22:52 by smbaabu           #+#    #+#             */
/*   Updated: 2019/06/09 13:51:47 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	print_digest(uint32_t *digest, t_ssl arg, int *flags)
{
	if (arg.type == 0)
	{
		if (flags[0])
		{
			ft_putendl(arg.name);
			free(arg.name);
		}
		join_print((uint8_t *)digest, 1);
	}
	if (arg.type == 1)
	{
		if (flags[2])
		{
			join_print((uint8_t *)digest, flags[1] ? 1 : 0);
			if (!flags[1])
				ft_printf(" %s\n", arg.name);
		}
		else
		{
			if (!flags[1])
				ft_printf("MD5 (%s) = ", arg.name);
			join_print((uint8_t *)digest, 1);
		}
	}
	if (arg.type == 2)
	{
		if (flags[2])
		{
			join_print((uint8_t *)digest, flags[1] ? 1 : 0);
			if (!flags[1])
				ft_printf(" %s\n", arg.name);
		}
		else
		{
			if (!flags[1])
				ft_printf("MD5 (\"%s\") = ", arg.name);
			join_print((uint8_t *)digest, 1);
		}
	}
}

void	process(t_ssl arg, uint32_t	*(*algorithm)(uint8_t *, uint64_t),
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
	{
		if (arg.error)
			no_such_file(arg.name, algo);
		else
			msg = read_file(arg.name, algo);
	}
	if (arg.type == 2)
	{
		if (arg.error)
			s_flag_error(algo);
		else
			msg = ft_strdup(arg.name);
	}
	if (msg)
	{
		digest = (*algorithm)((uint8_t *)msg, ft_strlen_llu((uint8_t *)msg));
		print_digest(digest, arg, flags);
		// free(msg);
		free(digest);
	}
}

void	dispatcher(char *algo, t_ssl *args, int no, int *flags)
{
	uint32_t	*(*algorithm)(uint8_t *, uint64_t);
	int			i;

	algorithm = ft_strequ("md5", algo) ? &md5 : &sha256;
	i = 0;
	while (i < no)
		process(args[i++], algorithm, flags, algo);
}

int		parse(char **av, int *flags, t_ssl *args)
{
	t_ssl	arg;
	int		i;
	int		idx;
	int		done;

	done = 0;
	idx = 0;
	i = 2;
	while (av[i] && i < 256)
	{
		if (!done)
		{
			if (ft_strequ(av[i], "-p"))
			{
				flags[0] = 1;
				args[idx++] = (t_ssl){NULL, 0, 0};
			}
			else if (ft_strequ(av[i], "-q"))
				flags[1] = 1;
			else if (ft_strequ(av[i], "-r"))
				flags[2] = 1;
			else if (ft_strequ(av[i], "-s"))
			{
				flags[3] = 1;
				arg = (t_ssl){NULL, 2, 0};
				if (av[++i])
					arg.name = av[i];
				else
					arg.error = 1;
				args[idx++] = arg;
			}
			else
			{
				done = 1;
				if (av[i][0] == '-' && av[i][1])
					args[idx++] = (t_ssl){av[i], -1, 1};
				else
					args[idx++] = (t_ssl){av[i], 1, 0};
			}
		}
		else
			args[idx++] = (t_ssl){av[i], 1, 0};
		i++;
	}
	if (!idx)
		args[idx++] = (t_ssl){NULL, 0, 0};
	return (idx);
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
