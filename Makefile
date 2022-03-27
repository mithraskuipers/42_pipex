# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/09 19:49:21 by mikuiper      #+#    #+#                  #
#    Updated: 2022/03/27 23:06:26 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc
FLAGS = -Wall -Werror -Wextra
LIB_FT = -lft -L $(FT_DIR) 
INC = -I $(INC_DIR) -I $(FT_INC)

FT_DIR = ./libft
FT_INC = $(FT_DIR)/inc/

INC_LST = pipex.h
INC_DIR = ./inc/
INC_PATHS = $(addprefix $(INC_DIR), $(INC_LST))

SRCS_DIR = ./src/
SRCS_LST = main.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LST))

DIR_OBJ = obj/
LST_OBJ = $(patsubst %.c, %.o, $(SRCS_LST))
OBJ_PATHS = $(addprefix $(DIR_OBJ), $(LST_OBJ))

GREEN = \033[92m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(FT) $(DIR_OBJ) $(OBJ_PATHS)
	@$(CC) $(FLAGS) $(INC) $(OBJ_PATHS) $(LIB_FT) -o $(NAME)
	@echo "$(GREEN)[$(NAME)] - $(GREEN)$(NAME) was compiled$(RESET)"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o : $(SRCS_DIR)%.c $(INC_PATHS)
	@$(CC) $(FLAGS) -c $(INC) $< -o $@

$(FT):
	@echo "[$(NAME)] - $(GREEN)Compiling $(FT)...$(RESET)"
	@$(MAKE) -sC $(FT_DIR)

clean:
	@$(MAKE) -sC $(FT_DIR) clean
	@rm -rf $(DIR_OBJ)
	@echo "$(GREEN)[$(NAME)] - $(RED)deleted $(DIR_OBJ)$(RESET)"
	@echo "$(GREEN)[$(NAME)] - $(RED)deleted all object files$(RESET)"

fclean: clean
	@rm -f $(FT)
	@echo "$(GREEN)[$(NAME)] - $(RED)deleted $(FT)$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)[$(NAME)] - $(RED)deleted ./$(NAME)$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re