/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:48:28 by alex              #+#    #+#             */
/*   Updated: 2024/02/27 15:29:11 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_color_from_texture(t_texture *txtr, float ray_len, char *buf,
	t_coord trgt)
{
	float	shadow;

	trgt.x *= txtr->size.x;
	trgt.y *= txtr->size.y;
	shadow = 0.3 / (ray_len + 1);
	buf[0] = (unsigned char)txtr->buf[0 + (int)trgt.y * 4 * txtr->size.x
		+ (int)trgt.x * 4] * shadow;
	buf[1] = (unsigned char)txtr->buf[1 + (int)trgt.y * 4 * txtr->size.x
		+ (int)trgt.x * 4] * shadow;
	buf[2] = (unsigned char)txtr->buf[2 + (int)trgt.y * 4 * txtr->size.x
		+ (int)trgt.x * 4] * shadow;
}

void	ft_wall_pixel_color(t_display *dis, t_ray *ray, char *buf, t_coord trgt)
{
	t_texture	*txtr;

	txtr = NULL;
	if (ray->target_type == TARGET_TYPE_WALL)
	{
		if (ray->target_orientation == ORIENTATION_S)
			txtr = &dis->wall_s;
		if (ray->target_orientation == ORIENTATION_N)
			txtr = &dis->wall_n;
		if (ray->target_orientation == ORIENTATION_W)
			txtr = &dis->wall_w;
		if (ray->target_orientation == ORIENTATION_E)
			txtr = &dis->wall_e;
	}
	else if (ray->target_type == TARGET_TYPE_EXIT)
		txtr = &dis->exit;
	else if (ray->target_type == TARGET_TYPE_DOOR)
		txtr = &dis->door;
	ft_get_color_from_texture(txtr, ray->length, buf, trgt);
}

void	ft_display_wall(t_game *game, t_coord_int pixel, int wall_size)
{
	t_coord		target;
	t_texture	img;

	img = game->display->img;
	target.y = (float)(pixel.y - game->player->pitch - ((DISPLAY_H - wall_size)
				/ 2)) / wall_size;
	target.x = game->ray[pixel.x]->target_column;
	ft_wall_pixel_color(game->display, game->ray[pixel.x], &img.buf
	[(pixel.y * DISPLAY_W + pixel.x) * 4], target);
	if (game->battery_lvl > 0 && game->flashlight)
		ft_flashlight(game, game->ray[pixel.x]->length, &img.buf
		[(pixel.y * DISPLAY_W + pixel.x) * 4], pixel);
}
