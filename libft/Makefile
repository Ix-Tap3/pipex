#==================================== MAKEFILE ====================================#

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
	   ft_strnlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	   ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
	   ft_strnstr.c ft_atoi.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c \
	   ft_split.c ft_strndup.c ft_freestrar.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c ft_count_digits.c print.c print_bases.c \
	   ft_putnbr_base_fd.c ft_putuint_base_fd.c get_next_line.c get_next_line_utils.c ft_lstnew_bonus.c \
	   ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	   ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_isempty.c ft_isspace.c
OBJS_DIR = objs
OBJS = ${SRCS:%.c=$(OBJS_DIR)/%.o}

#==================================== COLORS ====================================#

RESET   = \033[0m
BOLD    = \033[1m

PRIMARY = \033[38;2;10;189;198m
INFO    = \033[38;2;12;145;176m
ACCENT  = \033[38;2;14;123;165m
WARN    = \033[38;2;17;81;134m
ERROR   = \033[38;2;19;62;124m

#==================================== PHONY ====================================#

.PHONY: all clean fclean re

#==================================== RULES ====================================#  
all: $(NAME)

$(NAME): $(OBJS)
	@printf "\n"
	@printf "$(INFO)Archiving %s...$(RESET)\n" "$(NAME)"
	@ar rcs $(NAME) $(OBJS)
	@printf "$(PRIMARY)%s Ready !$(RESET)\n" "$(NAME)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@printf "\r$(ACCENT)Compiling object: %s$(RESET)\033[K" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(INFO)Cleaning $(NAME) objects...$(RESET)\n"
	@if [ -n "$(OBJS)" ]; then \
		for file in $(OBJS); do \
			printf "\r$(ACCENT)Cleaning $$file$(RESET)\033[K"; \
			rm -f $$file 2>/dev/null; \
			sleep 0.01; \
		done; \
	fi
	@printf "\r$(PRIMARY)$(NAME) objects cleaned!$(RESET)\033[K\n"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@printf "\n"
	@printf "$(ERROR)Cleanning %s...$(RESET)\n" "$(NAME)"
	@rm -rf $(NAME)

re: fclean all
