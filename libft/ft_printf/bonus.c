/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 20:36:36 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/16 21:03:14 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*b(va_list args, int *base)
{
	char *ret;

	*base = 2;
	ret = ft_itlu(va_arg(args, unsigned long long), *base, 0);
	return (ret);
}

static char	*convert_num(unsigned char c)
{
	char	*snum;
	char	*tmp;

	snum = ft_itoa_base_l(c, 16, 0);
	tmp = snum;
	snum = ft_strjoin("0x", snum);
	free(tmp);
	return (snum);
}

static int	handle_r(char *buf, char *ptr, int num)
{
	int		count;
	int		i;
	int		l;
	char	*snum;

	count = 0;
	i = 0;
	while (i < num)
	{
		if (!ft_isprint(ptr[i]))
		{
			snum = convert_num((unsigned char)ptr[i]);
			l = ft_strlen(snum);
			ft_memcpy(buf + count, snum, l);
			free(snum);
			count += l;
		}
		else
		{
			buf[i] = ptr[i];
			count++;
		}
		i++;
	}
	return (count);
}

char		*r(va_list args)
{
	char	buf[R_SIZE];
	int		num;
	char	*ptr;
	int		count;

	ptr = va_arg(args, char *);
	num = va_arg(args, unsigned int);
	if (ptr == NULL)
		ptr = ft_strdup(NULL_PRINT);
	else
	{
		count = handle_r(buf, ptr, num);
		ptr = (char *)malloc((1 + count) * sizeof(char));
		ft_memcpy(ptr, buf, count);
		ptr[count] = 0;
	}
	return (ptr);
}
