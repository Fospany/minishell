NAME = minishell

SOURCE =	split.c \
			minishell.c \
			split_helpers.c \
			rest_helpers.c \
			expansion_check.c \
			stepping_in_input.c \
			env_assign_helpers.c \
			syntax_error_check.c \
			environment_creation.c \
			dollar_sign_handler.c \
			env_assign.c \
			is_special_character.c \
			skippers.c \
			special_characters_checkers.c \
			tokenizing.c \
			word_count_helpers.c \



CFLAGS = -Wall -Wextra -Werror -g
READLINE_FLAG = -lreadline

CC = cc

LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a

OBJECTS = $(SOURCE:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME) : $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(SOURCE) $(LIBFT) -o $(NAME) $(READLINE_FLAG)

clean:
	@make -C $(LIBFT_DIR) clean
	rm -f $(OBJECTS)

fclean:
	@make -C $(LIBFT_DIR) fclean
	rm -f $(OBJECTS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
