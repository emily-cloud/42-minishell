# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlane <rlane@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 10:00:06 by rlane             #+#    #+#              #
#    Updated: 2024/06/06 19:14:13 by rlane            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# Source and object file directories
SRC_DIR = src
OBJ_DIR = obj

# Including directory
INC_DIR = include

# Source files
SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(addprefix ft_, \
	isalpha isdigit isalnum isascii isprint strlen memset bzero memcpy \
	memmove strlcpy strlcat toupper tolower strchr strrchr strncmp memchr \
	memcmp strnstr atoi calloc strdup substr strjoin strtrim split itoa \
	strmapi striteri putchar_fd putstr_fd putendl_fd putnbr_fd lstnew \
	lstadd_front lstsize lstlast lstadd_back lstdelone lstclear \
	lstiter lstmap \
	printf putnbr_functions char_functions format_handlers)))
SRC += $(addprefix $(SRC_DIR)/, $(addsuffix .c, get_next_line))

# Object files for main and bonus
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))


# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC -fPIE
CPPFLAGS = -I$(INC_DIR)

MAKE = make

# Default target
all: $(NAME)

# Main library compilation
$(NAME): $(OBJ)
	ar rcs $@ $^
	ranlib $@

# Object file compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean object files
clean:
	rm -f $(OBJ_DIR)/*.o

# Fully clean the project
fclean: clean
	rm -f $(NAME)

# Rebuild the project
re: fclean all

# Phony targets
.PHONY: all bonus clean clean_bonus fclean fclean_bonus re re_bonus
