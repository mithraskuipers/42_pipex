# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/25 11:43:09 by mikuiper      #+#    #+#                  #
#    Updated: 2022/02/25 11:49:19 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= pipex

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
#CFLAGS		= -Wall -fsanitize=address
RM			= rm -f

DIR_INC		= ./inc/
DIR_SRC		= ./src/

INC = -I include

SRC =	pipex.c

SRC_FULLPATH = $(addprefix $(DIR_SRC), $(SRC))
OBJ_FULLPATH = $(SRC_FULLPATH:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -I $(DIR_INC) -o $@ -c $?

$(NAME): $(OBJ_FULLPATH)
	$(CC) -o $(NAME) $(OBJ_FULLPATH) -I $(DIR_INC)

all: $(NAME)

clean:
	$(RM) $(OBJ_FULLPATH)

fclean:
	$(RM) $(NAME) $(OBJ_FULLPATH)

re: fclean all

PHONY: all clean fclean re