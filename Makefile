# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thifranc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/04 19:24:34 by thifranc          #+#    #+#              #
#    Updated: 2016/05/27 15:56:23 by thifranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

INC = lib.h

SRCS = parse go_tab draw_line

SRCS:= $(addsuffix .c, $(SRCS))
OBJ = $(SRCS:%.c=%.o)

FLAGS = -Wall -Werror -Wextra

OPT_FLAGS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	make re -C libft/
	make clean -C libft/
	gcc $(FLAGS) $(SRCS) libft/libft.a -o $(NAME) $(OPT_FLAGS)

clean:
	@$(RM) $(OBJ)
	@echo "erasing all binary files"

fclean: clean
	@$(RM) $(NAME)
	@make clean -C libft/
	@echo "erasing $(NAME)"

re: fclean all
	@make fclean -C libft/
	@echo "fclean + all"

.PHONY: all clean fclean re
