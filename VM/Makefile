# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjourdai <jjourdai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/21 19:01:09 by jjourdai          #+#    #+#              #
#    Updated: 2017/05/23 20:46:18 by fhenry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/

SRC_NAME = fill.c \
		fill2.c \
		vm_init.c \
		vm_init2.c \
		vm.c \
		vm2.c \
		debug.c \
		debug2.c \
		init_display.c \
		init_display2.c \
		init_display3.c \
		init_display4.c \
		init_display5.c \
		draw_border.c \
		draw_border2.c \
		francois.c \
		francois2.c \
		ft_int_to_char.c \
		ft_int_to_reg.c \
		op.c \
		ft_conv_to_int.c  \
		ft_powmod.c \
		core.c \
		core2.c \
		core3.c \
		function_op1.c \
		function_op2.c \
		function_op3.c \
		ft_add.c \
		ft_sub.c \
		ft_and.c \
		ft_or.c \
		ft_xor.c \
		ft_get_para.c \
		ft_get_para_without_idxmod.c \
		function_inter1.c \
		function_inter2.c \
		function_inter3.c \

OBJ_PATH = ./obj/

CPPFLAGS = -Iincludes -I ./libft/includes

LDFLAGS = -Llibft

LDLIBS = -lft

NAME = corewar

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

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
