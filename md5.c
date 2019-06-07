#include "ft_ssl.h"

char	*strpad_free(char *slen, int len)
{
	char	*ret;
	int		diff;

	ret = ft_strnew(64);
	diff = 64 - len;
	ft_memset(ret, '0', diff);
	ft_memcpy(ret + diff, slen, len);
	free(slen);
	return (ret);
}

char	*append(char *message, unsigned long long *mlen)
{
	char	*s, *slen;
	int		x, i, len;

	x = *mlen % 512;
	if (x > 448)
		i = 512 - x % 448;
	else if (x < 448)
		i = 448 - x;
	else
		i = 512;
	s = ft_strnewpad(i + 1, '0');
	s[0] = '1';
	slen = ft_itoa_llu(*mlen);
	slen = strpad_free(slen, ft_strlen(slen));
	*mlen = *mlen + 1 + i + 64;
	return join_free(s, slen);
}

void	calc(int *vars, int i, int *fg)
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
	vars[0] = f;
	vars[1] = g;
}

void	assign(int *dst, int *src)
{
	ft_memcpy_ints(dst, src, 4);
}

int		chunk(char *message, int g)
{
	char	*res;
	int		n;

	res = ft_strnew(sizeof(int));
	ft_memcpy(message + g * sizeof(int), res, sizeof(int));
	n = ft_atoi(res);
	return n;
}

int 	left_rotate(int n, int s)
{
	return ((n << s) | (n >> (32 - s)));
}

char	*join(int *vars)
{
	char	*a, *b, *c, *d, *res;

	a = ft_itoa(vars[0]);
	b = ft_itoa(vars[1]);
	c = ft_itoa(vars[2]);
	d = ft_itoa(vars[3]);
	res = join_free(a, b);
	res = join_free(res, c);
	return (join_free(res, d));
}

void	copy(int *vars)
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
	int cnts[4], vars[4], fg[2], i, j;

	message = append(message, &mlen);
	assign(cnts, (int[]){0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476});
	while (j < mlen)
	{
		assign(vars, cnts);
		while (i < 64)
		{
			calc(vars, i, fg);
			vars[0] = vars[1]
				+ left_rotate(
					vars[0] + fg[0] + g_k[i] + chunk(message + j, fg[1]),
					g_s[i]);
			copy(vars);
			i++;
		}
		ft_memcpy(cnts, vars, 4);
		j += 512;
	}
	join(vars);
}

int		main(int ac, char **av)
{
	if (ac == 2)
		md5(av[1], ft_strlen_llu(av[1]));
}