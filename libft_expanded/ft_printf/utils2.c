/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:31:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/17 15:39:25 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_neg(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-')
			return (i);
		i++;
	}
	return (-1);
}

int		isdigit_letter(char c)
{
	char *lower;
	char *upper;

	lower = "abcdef";
	upper = "ABCDEF";
	return (ft_strchr(lower, c) || ft_strchr(upper, c));
}

int		num_digits(const char *s)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) || isdigit_letter(s[i]))
			count++;
		i++;
	}
	return (count);
}

size_t	getlenllu(unsigned long long n, int base)
{
	int i;

	if (n == 0)
		return (1);
	i = 1;
	while (n /= base)
		i++;
	return (i);
}
