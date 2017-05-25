# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/17 13:28:01 by jjourdai          #+#    #+#              #
#*   Updated: 2017/03/06 14:29:20 by jjourdai         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./srcs/

SRC_NAME = main.c \
	   flag.c \
	   lexical.c \
	   error.c \
	   check.c \
	   op.c \
	create_table.c \
	print.c \
	choose.c \
	syntax.c \
		  
OBJ_PATH = ./obj/


CPPFLAGS = -Iincludes -I ./libft/includes

LDFLAGS = -Llibft

LDLIBS = -lft

NAME = asm

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.PHONY: all, clean, fclean, re

all: asm

asm: $(OBJ)
	make -C ./libft/
	$(CC) $^ -o $(NAME) $(LDFLAGS) $(LDLIBS)
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
