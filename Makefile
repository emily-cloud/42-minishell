# Variables
NAME = minishell
BONUS_NAME = minishell_bonus
SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = minishell.c init.c free.c  builtins.c parse.c tokenize_1.c tokenize_2.c tokenize_3.c content_to_args_1.c content_to_args_2.c env_list_1.c env_list_2.c \
			builtin_cd_1.c builtin_cd_2.c builtin_export.c exec_nodes.c expand_dollar_1.c expand_dollar_2.c expand_dollar_string.c exec_cmds_1.c exec_cmds_2.c redirect_in.c \
			redirect_out_append_1.c redirect_out_append_2.c signals.c heredoc_1.c heredoc_2.c heredoc_3.c pipe.c exec_and_or.c exec_sub_shell.c \
			input_error_check_1.c input_error_check_2.c builtins_echo.c builtins_echo_utils.c args_list_utils_1.c args_list_utils_2.c \
			nodes.c tree.c utils.c expand_wildcards_1.c expand_wildcards_2.c expand_wildcards_filter_ls_1.c expand_wildcards_filter_ls_2.c \
			print_debug.c
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(SRC_DIR) -I$(LIBFT_DIR)
LDFLAGS = -lreadline

# Colors
RED = \033[0;31m
ORANGE = \033[38;5;208m
YELLOW = \033[0;33m
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m

# Targets
all: $(NAME) $(BONUS_NAME)

bonus: $(BONUS_NAME)

$(LIBFT):
	@echo "$(YELLOW)Compiling libft..."
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)Linking $@..."
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME) -lreadline
	@echo "$(GREEN)$@ is ready!$(RESET)"

$(BONUS_NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)Linking $@..."
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(BONUS_NAME) -lreadline
	@echo "$(GREEN)$@ is ready!$(RESET)"

# Compilation rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(ORANGE)Compiling $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)Cleaning executables..."
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

fclean_all: fclean
	@echo "$(RED)Performing full clean...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)Starting full rebuild...$(RESET)"
	@$(MAKE) all

.PHONY: all clean fclean re

