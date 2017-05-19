
NAME = corewar

FILES = fill \
		vm_init \
		vm \
		debug\
		init_display \
		draw_border \
		francois \
		ft_int_to_char\
		ft_int_to_reg\
		op \
		ft_conv_to_int \
		ft_powmod \
		core \
		function_op
SRC = $(addsuffix .c, $(FILES))
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -g $(HEAD)
HEAD = -I./includes
LIB = ./libft

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB)
	@echo "Objects Files created."
	@$(CC) -o $(NAME) $(OBJ) -L$(LIB) -lft -lncurses
	@echo $(NAME) "created."

clean:
	@make clean -C $(LIB)
	@/bin/rm -f $(OBJ)
	@echo "Objects Files removed"

fclean: clean
	@make fclean -C $(LIB)
	@/bin/rm -f $(NAME)
	@echo $(NAME) "removed"

re: fclean all
