# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/15 21:13:40 by mikuiper      #+#    #+#                  #
#    Updated: 2022/04/15 21:18:26 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

INCS	=	-I./inc

SRC_DIR		= ./src/

SRCS		=	$(SRC_DIR)main.c \
				$(SRC_DIR)get_paths.c \
				$(SRC_DIR)strjoin.c \
				$(SRC_DIR)read.c \
				$(SRC_DIR)run_cmd.c

OBJS		= $(SRCS:.c=.o)

FT_DIR	=	./libft/
FT_MAKE	=	$(MAKE) -C $(FT_DIR)
FT_LIB		= -L$(FT_DIR) -lft

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
	@$(FT_MAKE) fclean
	@echo "$(GREEN)[pipex] - Running fclean..$(NOCOLOR)"
	@echo "$(GREEN)[pipex] - Removing object files..$(NOCOLOR)"
	@echo "$(GREEN)[pipex] - Finished running fclean!$(NOCOLOR)"
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re