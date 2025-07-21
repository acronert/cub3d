/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:47:05 by alex              #+#    #+#             */
/*   Updated: 2024/02/27 15:28:57 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_floor_pixel_color(t_game *game, char *buf, int y)
{
	float	shadow;

	shadow = (((float)y - (float)HALF_DISP_HEIGHT - (float)game->player->pitch)
			/ (float)DISPLAY_H);
	buf[2] = game->display->floor_color.red * shadow;
	buf[1] = game->display->floor_color.green * shadow;
	buf[0] = game->display->floor_color.blue * shadow;
}

void	ft_display_floor(t_game *game, t_coord_int pixel)
{
	t_texture		img;

	img = game->display->img;
	ft_floor_pixel_color(game, &img.buf
	[(pixel.y * DISPLAY_W + pixel.x) * 4], pixel.y);
	if (game->battery_lvl > 0 && game->flashlight)
		ft_flashlight(game, ((DISPLAY_H - pixel.y) / 10), &img.buf
		[(pixel.y * DISPLAY_W + pixel.x) * 4], pixel);
}
