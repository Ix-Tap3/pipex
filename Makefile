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
			 $(BONUS_DIR)/path_bonus.c $(BONUS_DIR)/pipex_bonus.c $(BONUS_DIR)/here_doc_bonus.c \
			 $(BONUS_DIR)/pipex_utils_bonus.c
OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJS_DIR)/%.o)

#==================================== COLORS ====================================#

RESET   = \033[0m
BOLD    = \033[1m

PRIMARY = \033[38;2;10;189;198m
INFO    = \033[38;2;12;145;176m
ACCENT  = \033[38;2;14;123;165m
WARN    = \033[38;2;17;81;134m
ERROR   = \033[38;2;19;62;124m

#==================================== HEADER ====================================#

define HEADER
@printf "\033[38;2;10;189;198m ||'''|,                             \033[0m\n"
@printf "\033[38;2;11;167;187m ||   ||  ''                         \033[0m\n"
@printf "\033[38;2;12;145;176m ||...|'  ||  '||''|, .|''|, \\\\\\\\  // \033[0m\n"
@printf "\033[38;2;14;123;165m ||       ||   ||  || ||..||   ><   \033[0m\n"
@printf "\033[38;2;16;101;144m.||      .||.  ||..|' \`|...  //  \\\\\\\\ \033[0m\n"
@printf "\033[38;2;17;81;134m               ||                   \033[0m\n"
@printf "\033[38;2;19;62;124m              .||                   \033[0m\n"
@printf "\n"
endef

#==================================== PHONY ====================================#

.PHONY: all bonus clean fclean re re_bonus header

#==================================== RULES ====================================#

all: header $(NAME)
	@printf "$(PRIMARY)Build Finished !$(RESET)\n"

header:
	$(HEADER)

$(LIB):
	@make --no-print-directory -C $(LIB_DIR)

$(NAME): $(OBJS) $(LIB)
	@printf "\n"
	@printf "$(INFO)Linking %s...$(RESET)\n" "$(NAME)"
	@$(CC) $(OBJS) -L$(LIB_DIR) -lft -o $(NAME)
	@printf "$(PRIMARY)%s Ready !$(RESET)\n" "$(NAME)"

bonus: header $(OBJS_BONUS) $(LIB)
	@printf "$(INFO)Linking %s with bonuses...$(RESET)\n" "$(NAME)"
	@$(CC) $(OBJS_BONUS) -L$(LIB_DIR) -lft -o $(NAME)
	@printf "$(PRIMARY)%s Ready !$(RESET)\n" "$(NAME)"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "\r$(ACCENT)Compiling object: %s$(RESET)\033[K" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean: header
	@printf "$(INFO)Cleaning $(NAME) objects...$(RESET)\n"
	@if [ -d "$(OBJS_DIR)" ]; then \
		for file in $(OBJS); do \
			printf "\r$(ACCENT)Cleaning $$file$(RESET)\033[K"; \
			rm -f $$file 2>/dev/null; \
		done; \
		printf "\n"; \
		rm -rf $(OBJS_DIR); \
	fi
	@make --no-print-directory -C $(LIB_DIR) clean
	@printf "\r$(PRIMARY)$(NAME) objects cleaned!$(RESET)\033[K\n"

fclean: header clean
	@printf "$(ERROR)Cleanning %s...$(RESET)\n" "$(NAME)"
	@printf "$(ERROR)Cleanning %s...$(RESET)\n" "$(LIB)"
	@rm -rf $(NAME)
	@rm -rf $(LIB)

re: header fclean all

re_bonus : header fclean bonus
