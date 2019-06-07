/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbaabu <smbaabu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:17:07 by smbaabu           #+#    #+#             */
/*   Updated: 2019/04/17 16:04:23 by smbaabu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "../libft.h"

# define S_CHAR 8
# define S_SHORT 16
# define S_INT 32
# define S_LONG 64
# define S_LONG_LONG 64
# define BUF_SIZE 1000000
# define R_SIZE 1000

# define SPECIFIERS "%cspdiouxXfbrkeg"
# define NON_SPECIFIERS "llhhL#0-+ .'"
# define MAGIC_CHR 1
# define NULL_PRINT "(null)"

# define PP 0
# define C 1
# define S 2
# define P 3
# define D 4
# define I 5
# define O 6
# define U 7
# define X 8
# define XX 9
# define F 10
# define B 11
# define R 12
# define K 13
# define E 14
# define G 15

# define UNITED_STATES 0
# define INTERNATIONAL 1

# define FLAGS "#-+0 '"
# define HASH 0
# define MINUS 1
# define PLUS 2
# define ZERO 3
# define SPACE 4
# define APOSTROPHE 5

# define BSE 0
# define SPCFR 1
# define PRCSN 2
# define MNWDTH 3

# define NUM_FLAGS 6
# define NUM_INFO 5

# define INDEX 0
# define COUNT 1
# define FLGS 2
# define BASE 3
# define NUL_COUNT 4

static const char	*g_months[] = {
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"June",
	"July",
	"Aug",
	"Sept",
	"Oct",
	"Nov",
	"Dec"
};

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define WHITE 	 "\033[01;37m"
# define RESET   "\x1b[0m"

int		ft_printf(const char *format, ...);
char	*apply_specifier(va_list args, int specifier, int modifier,
		int *info[]);
char	*apply_width(char *s, int min_width);
char	*apply_precision(char *s, int precision, int specifier);
char	*apply_flags(char *s, int *flags, int *info);

int		mantissa_length(char *binary);
char	*precision_g(char *s, int precision);

char	*apply_hash(char *s, int specifier, int precision, int base);
char	*apply_plus(char *s, int specifier, int min_width, int base);
char	*apply_zero(char *s, int specifier, int precision, int min_width);
char	*apply_space(char *s, int specifier, int min_width);
char	*apply_minus(char *s);
char	*apply_prefix(char *s, char *prefix);
char	*apply_apostrophe(char *s, int specifier);
char	*join_prefix(char *s, char *prefix);

int		check_validity(const char *s, int start);
int		check_specifier(const char *s, int start, int *upto);
int		check_modifier(const char *s, int start, int *upto);
int		check_precision(const char *s, int start, int *upto);
int		check_width(const char *s, int start, int *upto);
void	check_flags(const char *s, int start, int upto, int *flags);

char	*ft_itoa_ld(long double n);
char	*ft_itlu(unsigned long long n, int base, int upper);
char	*ft_itoa_base_l(long long n, int base, int upper);
char	*round_up(char *num, int precision);
char	*join_and_free(char *left, char *right);

char	*b(va_list args, int *base);
char	*r(va_list args);
char	*k(va_list args);
char	*e(char *f);
char	*g(char *f, char *e);

char	*create_str(char c, int *nul_count);
char	*copy(char *src, int n);
int		ft_stridx(const char *s, int c);
void	pre_print(char **s, int nul_count);
char	*strdup_wrapper(const char *s1);
size_t	getlen(long long n, int base);
size_t	getlenllu(unsigned long long n, int base);
int		*create_flags(int n);
void	clear_flags(int *flags, int n);
int		atleast_one(int *flags, int n);
int		**create_info(int *info[], int n);
void	destroy_info(int *info[], int n);
char	*ft_strnewpad(size_t n, char c);
int		check_neg(char *s);
int		num_digits(const char *s);

#endif
