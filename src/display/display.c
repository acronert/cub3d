/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:05:53 by alex              #+#    #+#             */
/*   Updated: 2024/02/26 13:51:03 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fps_counter(t_game *game, t_display *display)
{
	char			*tmp;
	static int		fps = 0;
	static int		old_time = 0;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_sec - old_time)
	{
		if (game->fps)
			free(game->fps);
		tmp = ft_itoa(fps);
		game->fps = ft_strjoin("FPS = ", tmp);
		free(tmp);
		fps = 0;
		old_time = current_time.tv_sec;
	}
	fps++;
	mlx_string_put(display->mlx, display->win, 10, 10, 0xFFFFFF, game->fps);
}

void	ft_draw_image(t_game *game)
{
	int				wall_size;
	int				ceiling_size;
	t_coord_int		pixel;

	pixel.x = -1;
	while (++pixel.x < DISPLAY_W)
	{
		pixel.y = -1;
		wall_size = (DISPLAY_H * WALL_HEIGHT) / (game->ray[pixel.x]->length);
		ceiling_size = ((DISPLAY_H - wall_size) / 2) + game->player->pitch;
		while (++pixel.y < DISPLAY_H)
		{
			if (pixel.y < ceiling_size)
				ft_display_ceiling(game, pixel);
			else if (pixel.y < (wall_size + ceiling_size))
				ft_display_wall(game, pixel, wall_size);
			else
				ft_display_floor(game, pixel);
		}
	}
}

void	ft_display(t_game *game)
{
	game->ray = ft_raycaster(game);
	ft_draw_image(game);
	ft_display_sprite(game);
	ft_draw_camera_overlay(game);
	mlx_put_image_to_window(game->display->mlx, game->display->win,
		game->display->img.img, 0, 0);
	if (game->mini_map)
		ft_draw_phone(&game->display->phone, game->display->img.buf);
	if (game->mini_map)
		ft_draw_minimap(game);
	ft_free_rays(game->ray);
	ft_fps_counter(game, game->display);
}
