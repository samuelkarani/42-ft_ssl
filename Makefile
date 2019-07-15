CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = ft_ssl

SRC = ft_ssl.c md5.c sha256.c parse.c print.c utils.c utils2.c utils3.c utils4.c debug.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)
	@make -C libft
	@make -C libft/ft_printf
	@make -C libft/get_next_line
	@$(CC) $(CFLAGS) $(OBJ) -Llibft -lft \
		-Llibft/ft_printf -lftprintf \
		-Llibft/get_next_line -lftget_next_line -o $@

clean:
	@make clean -C libft
	@make clean -C libft/ft_printf
	@make clean -C libft/get_next_line
	@rm -f $(OBJ)

fclean:
	@make fclean -C libft
	@make fclean -C libft/ft_printf
	@make fclean -C libft/get_next_line
	@rm -f $(OBJ)
	@rm -f $(NAME)

norm:
	norminette $(SRC) $(NAME).h

norm-all: norm
	norminette libft/{*.c,*.h} libft/ft_printf/{*.c,*.h} libft/get_next_line/{*.c,*.h}

re: fclean all

.PHONY: all clean fclean re norm norm-all
