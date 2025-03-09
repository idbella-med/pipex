NAME = pipex
CC 	= cc
FLAGS = -Wall -Wextra -Werror
HEADER = pipex.h Libft/libft.h

SRCS = main.c tools.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C Libft
	@$(CC) $(FLAGS) ./Libft/libft.a $(OBJS) -o $@

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make clean -C Libft 

fclean: clean
	@rm -f $(NAME)
	@make fclean -C Libft

re: fclean all

.PHONY: clean