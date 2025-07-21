/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_overlay.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:54:38 by alex              #+#    #+#             */
/*   Updated: 2024/02/22 15:19:56 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_battery_level(t_game *game, char *buf)
{
	t_coord_int	pixel;

	if (game->battery_lvl == 0)
		return ;
	pixel.y = BATTERY_OFFSET_Y;
	while (pixel.y < BATTERY_HEIGHT + BATTERY_OFFSET_Y)
	{
		pixel.x = BATTERY_OFFSET_X;
		while (pixel.x < (BATTERY_WIDTH * game->battery_lvl) + BATTERY_OFFSET_X)
		{
			if (game->battery_lvl <= 0.3)
				ft_pixtobuf(&buf[(pixel.y * DISPLAY_W + pixel.x) * 4],
					250, 50, 50);
			else
				ft_pixtobuf(&buf[(pixel.y * DISPLAY_W + pixel.x) * 4],
					200, 200, 200);
			pixel.x++;
		}
		pixel.y++;
	}
}

void	ft_draw_camera_overlay(t_game *game)
{
	t_coord_int		pixel;
	t_coord_int		trgt;
	t_texture		*txtr;
	char			*buf;

	buf = game->display->img.buf;
	txtr = &game->display->overlay;
	pixel.x = -1;
	while (++pixel.x < DISPLAY_W)
	{
		pixel.y = -1;
		while (++pixel.y < DISPLAY_H)
		{
			trgt.y = (float)(pixel.y * ((float)txtr->size.y / DISPLAY_H));
			trgt.x = (float)(pixel.x * ((float)txtr->size.x / DISPLAY_W));
			if ((unsigned char)txtr->buf[1 + (trgt.y * txtr->size.x + trgt.x)
					* 4] > 1)
			{
				ft_pixel_dup(&buf[0 + (pixel.y * DISPLAY_W + pixel.x) * 4],
					&txtr->buf[0 + (trgt.y * txtr->size.x + (int)trgt.x) * 4]);
			}
		}
	}
	ft_draw_battery_level(game, buf);
}
