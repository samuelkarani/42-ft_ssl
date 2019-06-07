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
	int		x, i;

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
	s = join_free(s, slen);
	slen = s;
	s = ft_strjoin(message, s);
	free(slen);
	return (s);
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
	fg[0] = f;
	fg[1] = g;
}

void	assign(int *dst, int *src)
{
	ft_memcpy_ints(dst, src, 4);
}

int		chunk(char *message, int g)
{
	return ((int)message + g * sizeof(int));
}

int 	left_rotate(int n, int s)
{
	return ((n << s) | (n >> (32 - s)));
}

void	join_print(int *vars)
{
	ft_printf("%x%x%x%x", vars[0], vars[1], vars[2], vars[3], vars[4]);
}

void	copy_round(int *vars)
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
	int cnts[4], vars[4], fg[2], i;
	unsigned long long	j;

	message = append(message, &mlen);
	assign(cnts, (int[]){0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476});
	j = 0;
	while (j < mlen)
	{
		assign(vars, cnts);
		i = 0;
		while (i < 64)
		{
			calc(vars, i, fg);
			vars[0] = vars[1]
				+ left_rotate(
					vars[0] + fg[0] + g_k[i] + chunk(message + j, fg[1]),
					g_s[i]);
			copy_round(vars);
			i++;
		}
		ft_memcpy_ints(cnts, vars, 4);
		j += 512;
	}
	join_print(vars);
	free(message);
}

int		main(int ac, char **av)
{
	if (ac == 2)
		md5(av[1], ft_strlen_llu(av[1]));
}