/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:43:59 by alex              #+#    #+#             */
/*   Updated: 2024/02/27 14:57:41 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_ceiling_pixel_color(t_game *game, char *buf)
{
	buf[2] = game->display->ceiling_color.red;
	buf[1] = game->display->ceiling_color.green;
	buf[0] = game->display->ceiling_color.blue;
}

void	ft_skybox_pixel_color(t_game *game, float ray_angle, int y, char *buf)
{
	t_coord		trgt;
	t_texture	txtr;

	txtr = game->display->skybox;
	trgt.x = txtr.size.x * (ray_angle / (2 * M_PI));
	trgt.y = (y - game->player->pitch + (HALF_DISP_HEIGHT))
		* (txtr.size.y / DISPLAY_H);
	if (trgt.x > txtr.size.x)
		trgt.x = txtr.size.x;
	else if (trgt.x < 0)
		trgt.x = 0;
	if (trgt.y > txtr.size.y)
		trgt.y = txtr.size.y;
	else if (trgt.y < 0)
		trgt.y = 0;
	ft_pixel_dup(&buf[0],
		&txtr.buf[0 + (int)(trgt.y * txtr.size.x + trgt.x)*4]);
}

void	ft_display_ceiling(t_game *game, t_coord_int pixel)
{
	t_texture		img;

	img = game->display->img;
	if (game->sky)
		ft_skybox_pixel_color(game, game->ray[pixel.x]->angle, pixel.y, &img.buf
		[(pixel.y * DISPLAY_W + pixel.x) * 4]);
	else
		ft_ceiling_pixel_color(game, &img.buf
		[(pixel.y * DISPLAY_W + pixel.x) * 4]);
}
