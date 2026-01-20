#==================================== MAKEFILE ====================================#

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LIB_DIR = libft
LIB = $(LIB_DIR)/libft.a
SRCS = main.c srcs/parser.c srcs/utils.c srcs/path.c
OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

#==================================== COLORS ====================================#

RESET   = \033[0m
BOLD    = \033[1m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m

#==================================== EMOJIS ====================================#

OK      = ✅
WARN    = ⚠️
CLEAN   = 🧹
BUILD   = 🔨
ROCKET  = 🚀

#==================================== PHONY ====================================#

.PHONY: all clean fclean re

#==================================== RULES ====================================#  
all: header $(NAME)
	@printf "$(GREEN)$(ROCKET)Build Finished !$(RESET)\n"

header:
	@printf "$(BLUE)$(BOLD)\n"
	@printf "==================================\n"
	@printf "       Building $(NAME)\n"
	@printf "==================================\n"
	@printf "$(RESET)\n"

$(LIB):
	@make --no-print-directory -C $(LIB_DIR)

$(NAME): $(OBJS) $(LIB)
	@printf "\n"
	@printf "$(YELLOW)$(BUILD) Linking %s...$(RESET)\n" "$(NAME)"
	@$(CC) $(OBJS) -L$(LIB_DIR) -lft -o $(NAME)
	@printf "$(GREEN)$(OK) %s Ready !$(RESET)\n" "$(NAME)"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "\r$(BLUE)$(BUILD) Compiling object: %s$(RESET)\033[K" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(YELLOW)$(CLEAN) Cleanning %s...$(RESET)\n" "$(OBJS)"
	@make --no-print-directory -C $(LIB_DIR) clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@printf "$(RED)$(CLEAN) Cleanning %s...$(RESET)\n" "$(NAME)"
	@rm -rf $(LIB)
	@rm -rf $(NAME)

re: fclean all
