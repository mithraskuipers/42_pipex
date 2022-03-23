# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/25 11:43:09 by mikuiper      #+#    #+#                  #
#    Updated: 2022/03/22 17:29:52 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

DIR_INC		= ./inc/
DIR_SRC		= ./src/

INC = -I include

SRC =	main.c \
		ft_split.c \
		ft_string.c \
		ft_print.c \
		close.c \
		paths.c \
		read.c \
		pipex.c

SRC_FULLPATH = $(addprefix $(DIR_SRC), $(SRC))
OBJ_FULLPATH = $(SRC_FULLPATH:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -I $(DIR_INC) -c $^ -o $@

$(NAME): $(OBJ_FULLPATH)
	$(CC) -o $(NAME) $(OBJ_FULLPATH) -I $(DIR_INC)

all: $(NAME)

clean:
	@echo "Running clean"
	@$(RM) $(OBJ_FULLPATH)

fclean: clean
	@echo "Running fclean"
	@$(RM) $(NAME) $(OBJ_FULLPATH)

re: fclean all

PHONY: all clean fclean re
