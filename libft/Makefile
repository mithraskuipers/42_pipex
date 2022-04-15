# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/21 15:29:25 by mikuiper      #+#    #+#                  #
#    Updated: 2022/04/15 21:10:51 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

GREEN = \033[92m
NOCOLOR = \033[0;38m
NAME = libft.a

SRCS =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_isupper.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_stoupper.c \
		ft_ndigits.c \
		ft_ndigits_base.c \
		ft_undigits_base.c \
		ft_itoa_base.c \
		ft_toabs.c \
		ft_utoa_base.c \
		ft_utoa.c \
		ft_countlines_fd.c \
		ft_strlen_fd.c \
		ft_strlen_char.c \
		mk_putnbr_base.c \
		ft_calloc_new.c \
		ft_strndup.c \
		ft_strchr_pos.c \
		dp_clean_char.c \
		dp_clean_void.c

OFILES = $(SRCS:.c=.o)
INCLUDES = libft.h

all: $(NAME)

$(NAME): $(OFILES) $(INCLUDES)
	@echo "$(GREEN)[libft] - Compiling library..$(NOCOLOR)"
	@ar rcs $(NAME) $?
	@echo "$(GREEN)[libft] - Done!$(NOCOLOR)"

%.o: %.c
	@$(CC) -Wall -Wextra -Werror -c $<

clean:
	@echo "$(GREEN)[libft] - Running clean..$(NOCOLOR)"
	@echo "$(GREEN)[libft] - Removing object files..$(NOCOLOR)"
	@/bin/rm -f $(OFILES)
	@echo "$(GREEN)[libft] - Finished running clean!$(NOCOLOR)"

fclean: clean
	@echo "$(GREEN)[libft] - Running fclean..$(NOCOLOR)"
	@echo "$(GREEN)[libft] - Removing libft.a..$(NOCOLOR)"
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)[libft] - Finished running fclean!$(NOCOLOR)"

re: fclean all
