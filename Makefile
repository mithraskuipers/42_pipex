NAME		= pipex

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

INCS	= -I./inc

SRC_DIR		= ./src/

SRCS		= $(SRC_DIR)main.c

OBJS		= $(SRCS:.c=.o)

FT_DIR	= 	./libft/
FT_MAKE	= $(MAKE) -C $(FT_DIR)
FT_LIB		= -L$(FT_DIR) -lft

.PHONY: all clean fclean re


GREEN = \033[92m
NOCOLOR = \033[0;38m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n$(GREEN)[pipex] - Compiling $(NAME)..$(NOCOLOR)"
	@$(FT_MAKE)
	@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(FT_LIB)

.c.o:
	@$(CC) $(CFLAGS) $(INCS) -c -o $@ $<

clean:
	$(FT_MAKE) clean
	@echo "$(GREEN)[pipex] - Running clean..$(NOCOLOR)"
	@echo "$(GREEN)[pipex] - Removing object files..$(NOCOLOR)"
	@$(RM) $(OBJS)
	@echo "$(GREEN)[pipex] - Finished running clean!$(NOCOLOR)"

fclean:
	#@$(FT_MAKE) fclean
	@echo "$(GREEN)[pipex] - Running fclean..$(NOCOLOR)"
	@echo "$(GREEN)[pipex] - Removing object files..$(NOCOLOR)"
	@echo "$(GREEN)[pipex] - Finished running fclean!$(NOCOLOR)"
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

re: fclean all