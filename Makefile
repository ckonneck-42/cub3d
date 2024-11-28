# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 12:14:45 by ckonneck          #+#    #+#              #
#    Updated: 2024/11/28 16:23:16 by ckonneck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Source files for cub3d
cub3d_SRCS = main.c keyhandling.c raycasting.c rendering.c parsing.c free.c
cub3d_OBJS = $(cub3d_SRCS:.c=.o)
cub3d_DEPS = $(cub3d_SRCS:.c=.d)
CC = cc
LIBFT_DIR = ./libft
LIBS = -L$(LIBFT_DIR) -lft -Lminilibx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -Imlx_linux
NAME = cub3d

all: $(NAME)

$(NAME): $(cub3d_OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(cub3d_OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) -O3 -MMD -c $< -o $@

-include $(cub3d_DEPS)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(cub3d_OBJS) $(cub3d_DEPS)


fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)


re: fclean all

# valgrind rule
valgrind: $(NAME)
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)
helgrind: $(NAME)
		valgrind --tool=helgrind --history-level=full ./$(NAME) $(ARGS)
# extra options: --verbose --log-file=valgrind-out.txt
#norminette rule
norminette: $(cub3d_SRCS)
		norminette $(cub3d_SRCS)

# Declare phony targets
.PHONY: all libft clean fclean re valgrind norminette