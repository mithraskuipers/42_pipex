NAME		= pipex

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

INCLUDES	= -I./inc

SRCDIR		= ./src/

SRCS		= $(SRCDIR)main.c

OBJS		= $(SRCS:.c=.o)

LIBFTPATH	= ./libft/
LIBFTMAKE	= $(MAKE) -C $(LIBFTPATH)
LIBFT		= -L$(LIBFTPATH) -lft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBFTMAKE)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	$(LIBFTMAKE) clean
	$(RM) $(OBJS)

fclean: clean
	$(LIBFTMAKE) fclean
	$(RM) $(NAME)

re: fclean all