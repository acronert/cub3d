# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/08 17:52:20 by acronert          #+#    #+#              #
#    Updated: 2024/12/23 17:31:33 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
CC			=	cc
FLAGS		= -g3 -O3
MLX_FLAGS	=	-Lmlx -lX11 -lXext -lm

FILES		=	src/main								\
				src/game/initialization					\
				src/game/init_textures					\
				src/game/thing_behavior					\
				src/game/thing_behavior_2				\
				src/game/game_event						\
				src/game/battery						\
				src/game/doors							\
				src/game/sprites						\
				src/game/exit							\
				src/raycaster/raycaster					\
				src/raycaster/ray_intersection			\
				src/raycaster/ray_collision				\
				src/raycaster/ray_collision_door		\
				src/raycaster/ray_collision_wall		\
				src/display/display						\
				src/display/minimap						\
				src/display/wall						\
				src/display/ceiling						\
				src/display/floor						\
				src/display/flashlight					\
				src/display/camera_overlay				\
				src/display/sprite						\
				src/display/sprite_utils				\
				src/pathfinder/pathfinder				\
				src/pathfinder/pathfinder_optimize		\
				src/pathfinder/pathfinder_utils			\
				src/pathfinder/pathfinder_utils_2		\
				src/pathfinder/floodfill				\
				src/input/input							\
				src/input/player_movement				\
				src/parsing/parsing						\
				src/parsing/parse_map_utils				\
				src/parsing/create_map					\
				src/parsing/parse_player				\
				src/parsing/parse_battery				\
				src/parsing/parse_thing					\
				src/parsing/parse_door					\
				src/parsing/parse_map					\
				src/parsing/parse_color					\
				src/parsing/parse_textures				\
				src/utils

HEADERS		=
LIBS		=	include/libft/libft.a			\
				minilibx-linux/libmlx.a			\
				minilibx-linux/libmlx_Linux.a
INCLUDE		=	-Iinclude -Iinclude/libft -Iminilibx-linux
SRCS		=	$(addsuffix .c, $(FILES))
OBJS		=	$(SRCS:.c=.o)

all:	$(NAME) display

$(NAME): $(OBJS) libft libmlx_linux libmlx
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS) $(MLX_FLAGS) -pthread

%.o: %.c
	@$(CC) $(FLAGS) -c $(INCLUDE) $< -o $@
	@echo "Compiling $@"

libft:
	@make -C include/libft/

libmlx_linux:
	@make -C minilibx-linux

libmlx:
	@make -C minilibx-linux

clean:
	@rm -rf $(OBJS)
	@make -C include/libft/ clean
	@echo "Cleaned $(NAME) object files"

fclean: clean
	@rm -rf $(NAME)
	@make -C include/libft/ fclean
	@echo "Cleaned $(NAME)"

re: fclean all

display:
	@echo ""
	@echo "\033[31m       ▄████▄   █    ██  ▄▄▄▄           ▓█████▄   \033[0m"
	@echo "\033[31m      ▒██▀ ▀█   ██  ▓██▒▓█████▄    ▄███▄ ▒██▀ ██▌ \033[0m"
	@echo "\033[31m      ▒▓█    ▄ ▓██  ▒██░▒██▒ ▄██   ▀ ▒▄██░██   █▌ \033[0m"
	@echo "\033[31m      ▒▓▓▄ ▄██▒▓▓█  ░██░▒██░█▀      ▄█▀  ░▓█▄  █  \033[0m"
	@echo "\033[31m      ▒ ▓███▀ ░▒▒█████▓ ░▓█  ▀█▓    ░░▀█▓░█████▀  \033[0m"
	@echo "\033[31m      ░ ░▒ ▒  ░░▒▓▒ ▒ ▒ ░▒▓███▀▒  ░▀███▀▒ ▒▒▓ ▒   \033[0m"
	@echo "\033[31m        ░  ▒   ░░▒░ ░ ░ ▒░▒   ░     ▒  ░  ░ ▒ ▒   \033[0m"
	@echo "\033[31m      ░         ░░░ ░ ░  ░    ░     ░  ░  ░ ░ ░   \033[0m"
	@echo "\033[31m      ░ ░         ░      ░          ░       ░     \033[0m"
	@echo "\033[31m      ░                       ░        ░  ░       \033[0m"
