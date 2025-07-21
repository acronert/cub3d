/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:36:23 by alex              #+#    #+#             */
/*   Updated: 2024/02/27 13:29:07 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_phone(t_texture *txtr, char *buf)
{
	t_coord_int		pixel;
	t_coord_int		trgt;

	pixel.x = PHONE_OFFSET_X;
	while (pixel.x < PHONE_OFFSET_X + PHONE_WIDTH)
	{
		pixel.y = PHONE_OFFSET_Y;
		while (pixel.y < PHONE_OFFSET_Y + PHONE_HEIGHT)
		{
			trgt.x = (float)((pixel.x - PHONE_OFFSET_X)
					* ((float)txtr->size.x / PHONE_WIDTH));
			trgt.y = (float)((pixel.y - PHONE_OFFSET_Y)
					* ((float)txtr->size.y / PHONE_HEIGHT));
			if ((unsigned char)txtr->buf
				[1 + (trgt.y * txtr->size.x + trgt.x) * 4] != 0)
			{
				ft_pixel_dup(&buf[0 + (pixel.y * DISPLAY_W + pixel.x) * 4],
					&txtr->buf[0 + (trgt.y * txtr->size.x + (int)trgt.x) * 4]);
			}
			pixel.y++;
		}
		pixel.x++;
	}
}

void	ft_calculate_minimap(t_game *game, t_coord_int pix, t_coord_int trgt)
{
	int	i;

	i = (int)(pix.y * (int)MINIMAP_WIDTH + pix.x)*4;
	if (trgt.x > game->map_size.x - 1 || trgt.x < 0
		|| trgt.y > game->map_size.y - 1 || trgt.y < 0)
		ft_pixtobuf(&game->display->minimap.buf[i], 0, 0, 0);
	else if ((pix.x == (int)MINIMAP_WIDTH / 2 && ((int)MINIMAP_HEIGHT / 2 - 10
				< pix.y && pix.y < (int)MINIMAP_HEIGHT / 2 + 10))
		|| (pix.y == ((int)MINIMAP_HEIGHT / 2)
			&& ((int)MINIMAP_WIDTH / 2 - 10 < pix.x
				&& pix.x < (int)MINIMAP_WIDTH / 2 + 10)))
		ft_pixtobuf(&game->display->minimap.buf[i], 0, 0, 0);
	else if (game->map[trgt.y][trgt.x] == ' ')
		ft_pixtobuf(&game->display->minimap.buf[i], 0, 0, 0);
	else if (game->map[trgt.y][trgt.x] == WALL)
		ft_pixtobuf(&game->display->minimap.buf[i], 225, 128, 0);
	else if (game->map[trgt.y][trgt.x] == EXIT_WALL)
		ft_pixtobuf(&game->display->minimap.buf[i], 64, 192, 64);
	else if (trgt.x == (int)((t_sprite *)game->sprite->content)->pos.x
		&& trgt.y == (int)((t_sprite *)game->sprite->content)->pos.y)
		ft_pixtobuf(&game->display->minimap.buf[i], 255, 0, 0);
	else
		ft_pixtobuf(&game->display->minimap.buf[i], 200, 200, 200);
}

void	ft_draw_minimap(t_game *game)
{
	t_coord_int	pix;
	t_coord_int	trgt;

	pix.x = 0;
	while (pix.x < (int)MINIMAP_WIDTH)
	{
		pix.y = 0;
		while (pix.y < (int)MINIMAP_HEIGHT)
		{
			trgt.x = game->player->pos.x + ((float)pix.x / (int)MINIMAP_WIDTH)
				* MINIMAP_ZOOM - MINIMAP_ZOOM / 2;
			trgt.y = game->player->pos.y + ((float)pix.y / (int)MINIMAP_HEIGHT)
				* MINIMAP_ZOOM - MINIMAP_ZOOM / 2;
			ft_calculate_minimap(game, pix, trgt);
			pix.y++;
		}
		pix.x++;
	}
	if (game->battery_lvl > 0.1)
		mlx_put_image_to_window(game->display->mlx, game->display->win,
			game->display->minimap.img, MINIMAP_OFFSET_X, MINIMAP_OFFSET_Y);
}
