#==================================== MAKEFILE ====================================#

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LIB_DIR = libft
LIB = $(LIB_DIR)/libft.a
SRCS_DIR = srcs
BONUS_DIR = $(SRCS_DIR)/bonus
SRCS = main.c $(SRCS_DIR)/parser.c $(SRCS_DIR)/utils.c $(SRCS_DIR)/path.c $(SRCS_DIR)/pipex.c
SRCS_BONUS = $(BONUS_DIR)/main_bonus.c $(BONUS_DIR)/parser_bonus.c $(BONUS_DIR)/utils_bonus.c \
			 $(BONUS_DIR)/path_bonus.c $(BONUS_DIR)/pipex_bonus.c
OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJS_DIR)/%.o)

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

bonus: $(OBJS_BONUS) $(LIB)
	@printf "\n"
	@printf "$(YELLOW)$(BUILD) Linking %s with bonuses...$(RESET)\n" "$(NAME)"
	@$(CC) $(OBJS_BONUS) -L$(LIB_DIR) -lft -o $(NAME)
	@printf "$(GREEN)$(OK) %s Ready !$(RESET)\n" "$(NAME)"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "\r$(BLUE)$(BUILD) Compiling object: %s$(RESET)\033[K" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(YELLOW)$(CLEAN) Cleaning $(NAME) objects...$(RESET)\n"
	@if [ -n "$OBJS" ]; then \
		for file in $(OBJS); do \
			printf "\r$(YELLOW)$(CLEAN) Cleaning $$file$(RESET)\033[K"; \
			rm -f $$file 2>/dev/null; \
			sleep 0.05; \
		done; \
	fi
	@printf "\r$(GREEN)$(OK) Objects cleaned!$(RESET)\033[K\n"
	@make --no-print-directory -C $(LIB_DIR) clean
	@rm -rf $(OBJS_DIR)

fclean: clean
	@printf "$(RED)$(CLEAN) Cleanning %s...$(RESET)\n" "$(NAME)"
	@printf "$(RED)$(CLEAN) Cleanning %s...$(RESET)\n" "$(LIB)"
	@rm -rf $(LIB)
	@rm -rf $(NAME)

re: fclean all
