#include "ft_ssl.h"

char	*pad_free(char *s, int n)
{
	int		i;
	char	*res;

	res = s;
	if (n < 8)
	{
		res = malloc(8 * sizeof(char));
		ft_memset(res, 0, 8);
		i = 7;
		while (--n >= 0)
			res[i--] = s[n] - '0';
		free(s);
	}
	return (res);
}

char	*append(char *message, unsigned long long *mlen)
{
	char	*res, *slen;
	int		i, x, n;

	x = *mlen % 64;
	if (x > 56)
		i = 64 - (x - 56);
	else if (x < 56)
		i = 56 - x;
	else
		i = 64;
	res = ft_memalloc(*mlen + i + 8);
	ft_memcpy(res, message, *mlen);
	res[*mlen] = (unsigned char)128;
	ft_memset(res + *mlen + 1, 0, i - 1);
	slen = ft_itoa_base(*mlen, 2);
	n = ft_strlen(slen);
	slen = pad_free(slen, n);
	ft_memcpy(res + *mlen + i, slen, 8);
	*mlen = *mlen + i + 8;
	return res;
}

void	compress(unsigned int *vars, int i, unsigned int *fg)
{
	int f, g;

	if (i >= 0 && i < 16)
	{
		f = (vars[1] & vars[2]) | (~vars[1] & vars[3]);
		g = i;
	}
	if (i >= 16 && i < 32)
	{
		f = (vars[3] & vars[1]) | (~vars[3] & vars[2]);
		g = (5 * i + 1) % 16;
	}
	if (i >= 32 && i < 48)
	{
		f = vars[1] ^ vars[2] ^ vars[3];
		g = (3 * i + 5) % 16;
	}
	if (i >= 48 && i < 64)
	{
		f = vars[2] ^ (vars[1] | ~vars[3]);
		g = (7 * i) % 16;
	}
	fg[0] = f;
	fg[1] = g;
}

void	assign(unsigned int *dst, unsigned int *src)
{
	ft_memcpy_ints(dst, src, 4);
}

unsigned int chunk(char *message, int g)
{
	return ((unsigned int)(message + g * sizeof(unsigned int)));
}

unsigned int left_rotate(unsigned int n, unsigned int s)
{
	return ((n << s) | (n >> (32 - s)));
}

void	update(unsigned int *dst, unsigned int *src)
{
	int i;

	i = 0;
	while (i < 4)
	{
		dst[i] += src[i];
		i++;
	}
}

void	copy_round(unsigned int *vars)
{
	int a, b, c, d;

	a = vars[0];
	b = vars[1];
	c = vars[2];
	d = vars[3];
	vars[0] = d;
	vars[1] = a;
	vars[2] = b;
	vars[3] = c;
}

void	md5(char *message, unsigned long long mlen)
{
	unsigned int cnts[4], vars[4], fg[2], i;
	unsigned long long	j;

	message = append(message, &mlen);
	assign(cnts, (unsigned int[]){0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476});
	j = 0;
	while (j < mlen)
	{
		assign(vars, cnts);
		i = 0;
		while (i < 3)
		{
			compress(vars, i, fg);
			vars[0] = vars[1]
				+ left_rotate(
					vars[0] + fg[0] + g_k[i] + chunk(message + j, fg[1]),
					g_s[i]);
			// print_hex(vars, 4); ft_putstr("\n");
			copy_round(vars);
			i++;
		}
		update(cnts, vars);
		j += 64;
	}
	join_print((unsigned char *)vars);
	free(message);
}

int		main(int ac, char **av)
{
	if (ac == 2)
		md5(av[1], ft_strlen_llu(av[1]));
}