# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tyassine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/30 17:55:39 by tyassine          #+#    #+#              #
#    Updated: 2016/06/20 17:34:04 by tyassine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INC = libft.h get_next_line.h ft_printf.h
FLAGS = -Wall -Wextra -Werror -c

SRCS = ft_atoi.c      ft_lstnew.c       ft_putstr.c       ft_strmap.c\
	ft_bzero.c        ft_memalloc.c     ft_putstr_fd.c    ft_strmapi.c\
	ft_isalnum.c      ft_memccpy.c      ft_strcat.c       ft_strncat.c\
	ft_isalpha.c      ft_memchr.c       ft_strchr.c       ft_strncmp.c\
	ft_isascii.c      ft_memcmp.c       ft_strclr.c       ft_strncpy.c\
	ft_isdigit.c      ft_memcpy.c       ft_strcmp.c       ft_strnequ.c\
	ft_isprint.c      ft_memdel.c       ft_strcpy.c       ft_strnew.c\
	ft_isspace.c      ft_memmove.c      ft_strdel.c       ft_strnstr.c\
	ft_iswhitespace.c ft_memset.c       ft_strdup.c       ft_strrchr.c\
	ft_itoa.c         ft_putchar.c      ft_strequ.c       ft_strsplit.c\
	ft_lstadd.c       ft_putchar_fd.c   ft_striter.c      ft_strstr.c\
	ft_lstdel.c       ft_putendl.c      ft_striteri.c     ft_strsub.c\
	ft_lstdelone.c    ft_putendl_fd.c   ft_strjoin.c      ft_strtrim.c\
	ft_lstiter.c      ft_putnbr.c       ft_strlcat.c      ft_tolower.c\
	ft_lstmap.c       ft_putnbr_fd.c    ft_strlen.c       ft_toupper.c\
	ft_strrev.c       ft_read_char.c    ft_isnl.c         ft_isstr_end.c\
	ft_strclen.c      get_next_line.c\
	ft_length_funcs.c ft_parse_and_store.c 					ft_print_all.c \
	ft_printf.c 	  utilities.c 		print_nocon.c 		decide_force.c \
	ft_small_functions.c 				ft_very_small_functions.c \
	ft_det_zeroes.c 	print_char.c \
	itoabase.c ft_memset.c \
	ft_putwidechar.c print_str.c print_wstr.c print_long.c ft_nbrlen.c\
	ft_wait.c ft_strgrab.c ft_atoi_addlen.c ft_getcfrstolst.c ft_abs.c ft_strndup.c\
	handle_int.c handle_oct.c handle_hex.c handle_nsg.c ft_putstrstr.c ft_putcharstr.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):
		@gcc $(FLAGS) $(SRCS) $(INC)
		@ar rc $(NAME) $(OBJS)

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: fclean all
.PHONY: clean fclean re
