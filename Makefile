# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: selcyilm <selcyilm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/11/24 20:36:11 by selcyilm      #+#    #+#                  #
#    Updated: 2024/12/23 20:10:19 by selcyilm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =dinner.c  init_table.c  main.c  parse_input.c  philo.c  print.c  printer.c  time.c  utils.c 

SRC_DIR = src
OBJ_DIR = obj
INCLUDE = include

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

#CC = cc -Wall -Werror -Wextra -g3 -fsanitize=address,undefined,leak
CC = cc -Wall -Werror -Wextra -g3 -fsanitize=thread -pthread

COLOUR_GREEN=\033[35m
COLOUR_BLUE=\033[0;36m
COLOUR_END=\033[0m
COLOUR_ORANGE=\033[38;5;214m

all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS)  -o $(NAME)
	@echo "$(COLOUR_ORANGE)PHILOSOPERS ARE READY TO GO..$(COLOUR_END)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) -I$(INCLUDE) -c $< -o $@
	@echo "$(COLOUR_GREEN)CREATING $@$(COLOUR_END)"

clean: 
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOUR_BLUE)CLEARING OBJECT FILES FOR PHILO$(COLOUR_END)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(COLOUR_BLUE)REMOVING EXECUTABLE FOR PHILO$(COLOUR_END)"

norm:
	norminette

re: fclean all

.PHONY: all clean fclean re