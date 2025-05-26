NAME        =   minishell
CC          =   cc
CFLAGS      =   -Wall -Wextra -Werror -g
RM          =   rm -rf

# Add the path to your libft directory
LIBFT_DIR   =   libft
LIBFT       =   $(LIBFT_DIR)/libft.a
LIBFT_INC   =   $(LIBFT_DIR)

# Readline path (this assumes the default installation location)
READLINE_INC =   -I/usr/include/readline
READLINE_LIB =   -lreadline

SRC         =   tokenize.c main.c utils.c inputs.c commands.c expander.c
OBJS        =   $(SRC:.c=.o)

# Include the libft directory and link libft
CFLAGS      +=  -I$(LIBFT_INC) $(READLINE_INC)  # Add libft and readline include directories to CFLAGS
LDFLAGS     =   $(LIBFT) $(READLINE_LIB)         # Link with the libft and readline libraries

all:    $(NAME)

$(NAME):    $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)	# Build the libft library if not built already

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean  # Clean libft objects

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean  # Clean libft library

re: fclean all

.PHONY: all clean fclean re