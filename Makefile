CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = ft_ssl

SRC = md5.c utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft
	@make -C libft/ft_printf
	@make -C libft/get_next_line
	@$(CC) $(CFLAGS) $(SRC) -Llibft -lft \
		-Llibft/ft_printf -lftprintf \
		-Llibft/get_next_line -lftget_next_line -o $@

clean:
	@make clean -C libft
	@make clean -C libft/ft_printf
	@make clean -C libft/get_next_line
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	@make fclean -C libft/ft_printf
	@make fclean -C libft/get_next_line
	@rm -f $(NAME)

norm:
	norminette $(SRC) ft_ls.h

norm-all: norm
	norminette libft/{*.c,*.h} libft/ft_printf/{*.c,*.h} libft/get_next_line/{*.c,*.h}

re: fclean all

.PHONY: all clean fclean re norm norm-all