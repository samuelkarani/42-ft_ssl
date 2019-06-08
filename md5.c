#include "ft_ssl.h"

uint8_t	*pad_free(uint8_t *s, int n)
{
	int		i;
	uint8_t	*res;

	res = s;
	if (n < 8)
	{
		res = malloc(8);
		ft_memset(res, 0, 8);
		i = 7;
		while (--n >= 0)
			res[i--] = s[n] - '0';
		free(s);
	}
	return (res);
}

uint8_t	*append(uint8_t *message, uint64_t *mlen)
{
	uint8_t		*res, *slen;
	uint32_t	i, x, n;

	x = *mlen % 64;
	if (x > 56)
		i = 64 - (x - 56);
	else if (x < 56)
		i = 56 - x;
	else
		i = 64;
	res = ft_memalloc(*mlen + i + 8);
	ft_memcpy(res, message, *mlen);
	res[*mlen] = (u_int8_t)128;
	ft_memset(res + *mlen + 1, 0, i - 1);
	slen = ft_itoa_base_llu(*mlen, 2);
	n = ft_strlen((char *)slen);
	slen = pad_free(slen, (int)n);
	ft_memcpy(res + *mlen + i, slen, 8);
	*mlen = *mlen + i + 8;
	return res;
}

void	compress(uint32_t *vars, size_t i, uint32_t *fg)
{
	uint32_t f, g;

	if (i < 16)
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

void	assign(uint32_t *dst, uint32_t *src)
{
	ft_memcpy_ints(dst, src, 4);
}

uint32_t chunk(uint8_t *message, size_t g)
{
	uint32_t n;

	n = (uint32_t)(message + g * 4);
	return (n);
}

uint32_t left_rotate(uint32_t n, uint32_t s)
{
	return ((n << s) | (n >> (32 - s)));
}

void	update(uint32_t *dst, uint32_t *src)
{
	int i;

	i = 0;
	while (i < 4)
	{
		dst[i] += src[i];
		i++;
	}
}

void	copy_round(uint32_t *vars)
{
	uint32_t a, b, c, d;

	a = vars[0];
	b = vars[1];
	c = vars[2];
	d = vars[3];
	vars[0] = d;
	vars[1] = a;
	vars[2] = b;
	vars[3] = c;
}

void	md5(uint8_t *message, uint64_t mlen)
{
	uint32_t cnts[4], vars[4], fg[2], i;
	uint64_t	j;

	message = append(message, &mlen);
	print_binary_char(message, mlen);
	assign(cnts, (uint32_t[]){0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476});
	j = 0;
	while (j < mlen)
	{
		assign(vars, cnts);
		i = 0;
		while (i < 64)
		{
			compress(vars, i, fg);
			vars[0] = vars[1]
				+ left_rotate(
					vars[0] + fg[0] + g_k[i] + chunk(message + j, fg[1]),
					g_s[i]);
			copy_round(vars);
			print_hex_ints(vars, 4);
			print_binary_ints(vars, 4);
			i++;
		}
		update(cnts, vars);
		j += 64;
	}
	join_print((u_int8_t *)vars);
	free(message);
}

int		main(int ac, char **av)
{
	if (ac == 2)
		md5((uint8_t *)av[1], ft_strlen_llu((uint8_t *)av[1]));
}