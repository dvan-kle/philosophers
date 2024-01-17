# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dvan-kle <dvan-kle@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/14 21:47:54 by dvan-kle      #+#    #+#                  #
#    Updated: 2024/01/17 20:33:31 by dvan-kle      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CC_FLAGS = -Wall -Wextra -g -fsanitize=thread
SRC = src/main.c src/input.c src/time.c src/utils.c src/routine.c

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF)
	$(CC) $(CC_FLAGS) $(OBJ) -o $(NAME)
	@echo "\033[32mBuild complete\033[0m"

$(OBJ_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all