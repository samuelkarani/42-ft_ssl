/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 19:10:19 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/15 17:32:02 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*p(va_list args, int *base, int *flags)
{
	char *ret;

	ret = ft_itoa_base_l(va_arg(args, long), 16, 0);
	*base = 16;
	flags[HASH] = 1;
	return (ret);
}

static char	*di(va_list args, int modifier, int *base)
{
	char *ret;

	ret = NULL;
	*base = 10;
	if (modifier != -1)
	{
		if (modifier == 1)
			ret = ft_itoa_base_l((char)va_arg(args, int), *base, 0);
		if (modifier == 2)
			ret = ft_itoa_base_l((short)va_arg(args, int), *base, 0);
		if (modifier == 3)
			ret = ft_itoa_base_l(va_arg(args, long), *base, 0);
		if (modifier == 4)
			ret = ft_itoa_base_l(va_arg(args, long long), *base, 0);
	}
	else
		ret = ft_itoa_base_l(va_arg(args, int), *base, 0);
	return (ret);
}

static char	*ouxx(va_list args, int specifier, int modifier, int *base)
{
	char	*ret;
	int		u;

	ret = NULL;
	u = specifier == XX;
	if (specifier == O)
		*base = 8;
	if (specifier == U)
		*base = 10;
	if (specifier == X || specifier == XX)
		*base = 16;
	if (modifier != -1)
	{
		if (modifier == 1)
			ret = ft_itlu((unsigned char)va_arg(args, unsigned int), *base, u);
		if (modifier == 2)
			ret = ft_itlu((unsigned short)va_arg(args, unsigned int), *base, u);
		if (modifier == 3)
			ret = ft_itlu(va_arg(args, unsigned long), *base, u);
		if (modifier == 4)
			ret = ft_itlu(va_arg(args, unsigned long long), *base, u);
	}
	else
		ret = ft_itlu(va_arg(args, unsigned int), *base, u);
	return (ret);
}

static char	*feg(va_list args, int specifier, int modifier, int *base)
{
	char	*ret;

	*base = 10;
	if (modifier != -1)
	{
		if (modifier == 3)
			ret = ft_itoa_ld(va_arg(args, double));
		if (modifier == 5)
			ret = ft_itoa_ld(va_arg(args, long double));
	}
	else
		ret = ft_itoa_ld(va_arg(args, double));
	if (specifier == E)
		ret = e(ret);
	if (specifier == G)
		ret = g(ft_strdup(ret), e(ret));
	return (ret);
}

char		*apply_specifier(va_list args, int specifier, int modifier,
	int *info[])
{
	char	*ret;

	ret = NULL;
	if (specifier == PP)
		ret = create_str('%', 0);
	if (specifier == C)
		ret = create_str((char)va_arg(args, int), info[NUL_COUNT]);
	if (specifier == S)
		ret = strdup_wrapper(va_arg(args, char *));
	if (specifier == P)
		ret = p(args, info[BASE], info[FLGS]);
	if (specifier == D || specifier == I)
		ret = di(args, modifier, info[BASE]);
	if (specifier >= O && specifier <= XX)
		ret = ouxx(args, specifier, modifier, info[BASE]);
	if (specifier == F || specifier == E || specifier == G)
		ret = feg(args, specifier, modifier, info[BASE]);
	if (specifier == B)
		ret = b(args, info[BASE]);
	if (specifier == R)
		ret = r(args);
	if (specifier == K)
		ret = k(args);
	return (ret);
}
