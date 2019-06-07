/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 20:42:30 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/15 21:41:09 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	apply_args(const char *format, va_list args, int *info[],
	char **ret)
{
	int		i;
	int		idx;
	int		specifier;
	int		min_width;
	int		upto;

	i = *info[INDEX];
	specifier = check_specifier(format, i + 1, &upto);
	*info[INDEX] = upto;
	idx = check_modifier(format, i + 1, &upto);
	*ret = apply_specifier(args, specifier, idx, info);
	if ((idx = check_precision(format, i + 1, &upto)) != -1
		|| specifier == F || specifier == E || specifier == G)
		*ret = apply_precision(*ret, idx, specifier);
	if ((min_width = check_width(format, i + 1, &upto)) != -1)
		*ret = apply_width(*ret, min_width);
	check_flags(format, i + 1, upto, info[FLGS]);
	if (atleast_one(info[FLGS], NUM_FLAGS) != -1)
		*ret = apply_flags(*ret, info[FLGS],
			(int[]){*info[BASE], specifier, idx, min_width});
}

static void	update_buf(char *buf, const char *src, int len, int *info[])
{
	ft_memcpy(buf + *info[COUNT], src, len);
	*info[COUNT] += len;
}

static void	handle_args(const char *format, va_list args, int *info[],
	char *buf)
{
	char	*ret;
	int		len;

	*info[BASE] = 0;
	*info[NUL_COUNT] = 0;
	apply_args(format, args, info, &ret);
	len = ft_strlen(ret);
	pre_print(&ret, *info[NUL_COUNT]);
	update_buf(buf, ret, len, info);
	free(ret);
	clear_flags(info[FLGS], NUM_FLAGS);
}

int			ft_printf(const char *format, ...)
{
	int		*info[NUM_INFO];
	int		count;
	va_list	args;
	char	buf[BUF_SIZE];

	va_start(args, format);
	create_info(info, NUM_INFO);
	free(info[FLGS]);
	info[FLGS] = create_flags(NUM_FLAGS);
	*info[COUNT] = 0;
	*info[INDEX] = 0;
	while (format[*info[INDEX]])
	{
		if (format[*info[INDEX]] == '%'
			&& check_validity(format, *info[INDEX] + 1) != -1)
			handle_args(format, args, info, buf);
		else if (format[*info[INDEX]] != '%')
			update_buf(buf, &format[*info[INDEX]], 1, info);
		(*info[INDEX])++;
	}
	va_end(args);
	count = *info[COUNT];
	destroy_info(info, NUM_INFO);
	return (write(1, buf, count));
}
