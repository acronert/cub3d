/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <mshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:49:53 by acronert          #+#    #+#             */
/*   Updated: 2024/02/28 14:46:03 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_mlx(t_display *display)
{
	display->mlx = mlx_init();
	if (!display->mlx)
		return (FAILURE);
	display->win = mlx_new_window(display->mlx, DISPLAY_W, DISPLAY_H, "cub3d");
	if (!display->win)
		return (FAILURE);
	display->img.img = mlx_new_image(display->mlx, DISPLAY_W, DISPLAY_H);
	if (!display->img.img)
		return (FAILURE);
	display->img.bpp = BPP;
	display->img.line_size = 4 * display->img.size.x;
	display->img.buf = mlx_get_data_addr(display->img.img, &display->img.bpp,
			&display->img.line_size, &display->img.endian);
	if (!display->img.buf)
		return (FAILURE);
	display->img.path = NULL;
	display->img.size.x = DISPLAY_W;
	display->img.size.y = DISPLAY_H;
	return (SUCCESS);
}

void	ft_init_minimap(t_display *display)
{
	display->minimap.img = mlx_new_image(display->mlx, MINIMAP_WIDTH,
			MINIMAP_HEIGHT);
	display->minimap.bpp = BPP;
	display->minimap.line_size = 4 * MINIMAP_WIDTH;
	display->minimap.buf = mlx_get_data_addr(display->minimap.img,
			&display->minimap.bpp, &display->minimap.line_size,
			&display->minimap.endian);
	display->minimap.path = NULL;
	display->minimap.size.x = MINIMAP_WIDTH;
	display->minimap.size.y = MINIMAP_HEIGHT;
}

void	ft_init_game_settings(t_game *game)
{
	struct timeval	current_time;

	srand(time(NULL));
	gettimeofday(&current_time, NULL);
	game->start_time = current_time.tv_sec;
	game->map_size.x = ft_strlen(game->map[0]);
	game->map_size.y = ft_arrlen(game->map);
	game->flashlight = 1;
	game->sky = 1;
	game->mini_map = 0;
	game->space_bar = 0;
	game->flashlight_offset.x = 0;
	game->flashlight_offset.y = 0;
	game->battery_lvl = 1;
	game->pursuit = 0;
	game->thing_path = NULL;
	game->fps = NULL;
	game->key_pressed.m_up = 0;
	game->key_pressed.m_down = 0;
	game->key_pressed.m_left = 0;
	game->key_pressed.m_right = 0;
	game->key_pressed.r_left = 0;
	game->key_pressed.r_right = 0;
	game->key_pressed.r_up = 0;
	game->key_pressed.r_down = 0;
}

t_game	*ft_initialization(char *filename)
{
	t_game			*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	if (ft_parsing(game, filename, -1) == FAILURE)
		ft_exit(game);
	if (ft_init_mlx(game->display) == FAILURE)
		ft_exit(game);
	ft_init_minimap(game->display);
	if (ft_import_textures(game->display) == FAILURE)
		ft_exit(game);
	ft_init_game_settings(game);
	return (game);
}
