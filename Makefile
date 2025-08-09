# Basic Makefile for stat-system project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude
NAME = stat-system
OBJ_DIR = obj

# Source files
SRCS =	main.c \
		src/utils/utils.c \
		src/utils/print_stats.c \
		src/entities/player.c \
		src/entities/enemy.c \
		src/core/loop.c \
		src/utils/debug.c
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(NAME)

# Main executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

# Object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

# Clean targets
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Phony targets
.PHONY: all clean fclean re
