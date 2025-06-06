# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: selcyilm <selcyilm@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/11/24 20:36:11 by selcyilm      #+#    #+#                  #
#    Updated: 2025/05/05 16:34:31 by selcyilm      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = eat_sleep_think.c fn_error.c fn_parse.c fn_start.c  monitor.c time_utils.c \
fn_clean.c fn_init.c fn_print_msg.c main.c thread_utils.c

SRC_DIR = src
OBJ_DIR = obj
INCLUDE = -I include

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

#CC = cc -Wall -Werror -Wextra -g3 -fsanitize=address,undefined,leak
CC = cc -Wall -Werror -Wextra -g3 -fsanitize=thread -pthread

COLOUR_GREEN=\033[32;01m
COLOUR_BLUE=\033[0;36m
COLOUR_END=\033[0m
COLOUR_ORANGE=\033[38;5;214m

all: $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "$(COLOUR_ORANGE)PHILOSOPERS ARE READY TO GO..$(COLOUR_END)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) -c $< -o $@
	@echo "Compiling $(COLOUR_GREEN)$<$(COLOUR_END)"

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