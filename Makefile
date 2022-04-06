# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/04/06 10:25:24 by mikuiper      #+#    #+#                  #
#    Updated: 2022/04/06 17:32:50 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
FLAGS = -Wall -Werror -Wextra
LIB_FT = -lft -L $(FT_DIR) 
INC = -I $(INC_DIR) -I $(FT_INC)

FT_DIR = ./libft
FT_INC = $(FT_DIR)/inc/
FT = $(FT_DIR)/libft.a

INC_LST = pipex.h
INC_DIR = ./inc/
INC_PATHS = $(addprefix $(INC_DIR), $(INC_LST))

SRCS_DIR = ./src/
SRCS_LST =	main.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LST))

DIR_OBJ = obj/
LST_OBJ = $(patsubst %.c, %.o, $(SRCS_LST))
OBJ_PATHS = $(addprefix $(DIR_OBJ), $(LST_OBJ))

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(FT) $(DIR_OBJ) $(OBJ_PATHS)
	@$(CC) $(FLAGS) $(LIB_FT) $(INC) $(OBJ_PATHS) -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was compiled$(RESET)"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o : $(SRCS_DIR)%.c $(INC_PATHS)
	@$(CC) $(FLAGS) -c $(INC) $< -o $@

$(FT):
	@echo "$(NAME): $(GREEN)Compiling $(FT)...$(RESET)"
	@$(MAKE) -sC $(FT_DIR)

clean:
	#@$(MAKE) -sC $(FT_DIR) clean
	@rm -rf $(DIR_OBJ)
	@echo "$(RESET)$(NAME): $(RED)deleted $(DIR_OBJ)$(RESET)"
	@echo "$(NAME): $(RED)deleted all object files$(RESET)"

fclean: clean
	#@rm -f $(FT)
	#@echo "$(NAME): $(RED)deleted $(FT)$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)deleted ./$(NAME)$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
