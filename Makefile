NAME = pipex
COMP = cc
FLAGS = -Wall -Wextra -Werror
SRC = pipex.c
HEADER = pipex.h
OBJ = $(src.c:.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(COMP) $(FLAGS) $< -o $(NAME)

%.o:%.c $(HEADER)
	$(COMP) $(FLAGS) $< -c -o $@

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.Phony : clean