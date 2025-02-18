NAME = pipex
COMP = cc
FLAGS = -Wall -Wextra -Werror
SRC = pipex.c
HEADER = pipex.h
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@make re -C libft
	$(COMP) $(FLAGS) $(OBJ) ./libft/libft.a -o $(NAME)

%.o: %.c $(HEADER)
	$(COMP) $(FLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ)
	@make clean -C libft

fclean : clean
	rm -rf $(NAME)
	@make fclean -C libft

re : fclean all

.Phony : clean