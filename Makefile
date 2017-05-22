# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/21 19:01:09 by jjourdai          #+#    #+#              #
#    Updated: 2017/05/22 14:04:05 by syusof           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/

SRC_NAME = fill.c \
		vm_init.c \
		vm.c \
		debug.c \
		init_display.c \
		draw_border.c \
		francois.c \
		ft_int_to_char.c \
		ft_int_to_reg.c \
		op.c \
		ft_conv_to_int.c  \
		ft_powmod.c \
		core.c \
		function_op.c \
		function_op2.c \
		debug2.c \

OBJ_PATH = ./obj/

CPPFLAGS = -Iincludes -I ./libft/includes

LDFLAGS = -Llibft

LDLIBS = -lft

NAME = corewar

CC = gcc

CFLAGS = -Wall -Wextra -g

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.PHONY: all, clean, fclean, re

all: corewar

corewar: $(OBJ)
	make -C ./libft/
	$(CC) $^ -o $(NAME) $(LDFLAGS) $(LDLIBS) -lncurses
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -fv $(OBJ)
	make clean -C ./libft/
	@rmdir $(OBJ_PATH) 2> dev/null || true

fclean: clean
	make fclean -C ./libft/
	rm -fv $(NAME)

re: fclean all
