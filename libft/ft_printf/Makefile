CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
NAME = libftprintf.a
SRC = ft_printf.c specifier.c min_width.c precision.c flags.c \
		flags2.c flags3.c conversions.c conversions2.c checks.c \
		checks2.c utils.c utils2.c utils3.c bonus.c bonus_k.c \
		bonus_e.c bonus_g.c precision2.c flags4.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm
