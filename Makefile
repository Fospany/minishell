NAME = minishell

SOURCE =	split.c \
			minishell.c \
			split_helpers.c \
			stepping_in_input.c \
			env_assign_helpers.c \
			syntax_error_check.c 


CFLAGS = -Wall -Wextra -Werror -g

CC = cc

OBJECTS = $(SOURCE:.c=.o)

$(NAME) : $(OBJECTS)
		$(CC) $(CFLAGS) $(SOURCE) -o $(NAME)


all: $(NAME)

clean:
	rm -f $(OBJECTS)

fclean:
	rm -f $(OBJECTS)
	rm -f $(NAME)

re: fclean all


.PHONY = all clean fclean re