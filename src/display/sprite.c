/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:56:58 by alex              #+#    #+#             */
/*   Updated: 2024/12/23 17:25:26 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sprite_pixel_color(t_game *game, t_coord_int pix, t_coord trgt,
			t_sprite *sprite)
{
	float		shadow;
	char		*buf;
	t_texture	texture;

	texture = ft_get_sprite_texture(game, sprite);
	buf = game->display->img.buf;
	shadow = 0.3 / (sprite->distance + 1);
	if (trgt.y > texture.size.y || trgt.y < 0)
		trgt.y = 0;
	if (trgt.x > texture.size.x || trgt.x < 0)
		trgt.x = 0;
	if ((unsigned char)texture.buf
		[1 + ((int)trgt.y * texture.size.x + (int)trgt.x) * 4] > 0)
	{
		buf[0 +(pix.y * DISPLAY_W + pix.x) * 4] = (unsigned char)texture.buf
		[0 + ((int)trgt.y * texture.size.x + (int)trgt.x) * 4] * shadow;
		buf[1 +(pix.y * DISPLAY_W + pix.x) * 4] = (unsigned char)texture.buf
		[1 + ((int)trgt.y * texture.size.x + (int)trgt.x) * 4] * shadow;
		buf[2 +(pix.y * DISPLAY_W + pix.x) * 4] = (unsigned char)texture.buf
		[2 + ((int)trgt.y * texture.size.x + (int)trgt.x) * 4] * shadow;
		if (game->flashlight)
			ft_flashlight(game, sprite->distance, &buf
			[0 +(pix.y * DISPLAY_W + pix.x) * 4], pix);
	}
}

void	ft_draw_sprite_utils(t_sprite *sprite, t_coord_int *pix,
			t_coord_int off)
{
	sprite->frame++;
	if (sprite->frame >= sprite->frame_nb)
		sprite->frame = 0;
	pix->x = off.x;
	if (pix->x < 0)
		pix->x = 0;
}

void	ft_draw_sprite(t_game *game, t_coord size, t_coord_int off,
			t_sprite *sprite)
{
	t_coord_int	pix;
	t_coord		trgt;
	t_texture	txtr;

	txtr = ft_get_sprite_texture(game, sprite);
	ft_draw_sprite_utils(sprite, &pix, off);
	while (pix.x < off.x + size.x && pix.x < DISPLAY_W)
	{
		if (game->ray[pix.x]->length > sprite->distance)
		{
			pix.y = off.y - 1;
			if (pix.y < 0)
				pix.y = -1;
			while (++pix.y < off.y + size.y && pix.y < DISPLAY_H)
			{
				trgt.y = (float)(pix.y - off.y)*((float)txtr.size.y / size.y);
				trgt.x = (float)(pix.x - off.x)*(((float)txtr.size.x
							/ (sprite->frame_nb / 10)) / size.x)
					+ (sprite->frame / 10) * ((float)txtr.size.x
						/ (sprite->frame_nb / 10));
				ft_sprite_pixel_color(game, pix, trgt, sprite);
			}
		}
		pix.x++;
	}
}

void	ft_display_sprite(t_game *game)
{
	float		prev_max_dist;
	t_list		*farthest;
	t_coord		siz;
	t_coord_int	off;
	t_texture	texture;

	prev_max_dist = game->map_size.x + game->map_size.y;
	while (1)
	{
		farthest = ft_find_farthest_sprite(game->sprite, &prev_max_dist);
		if (!farthest)
			break ;
		siz.x = DISPLAY_W / (((t_sprite *)farthest->content)->distance + 1);
		siz.y = 2 * DISPLAY_H / (((t_sprite *)farthest->content)->distance + 1);
		off.x = ft_find_sprite_center(game, farthest) - (siz.x / 2);
		off.y = (DISPLAY_H - siz.y) / 2 + game->player->pitch + (siz.y / 4.0);
		if (((t_sprite *)farthest->content)->type == TYPE_THING)
			texture = game->display->the_thing;
		else if (((t_sprite *)farthest->content)->type == TYPE_BATTERY)
			texture = game->display->battery;
		if (off.x > -siz.x && off.x < DISPLAY_W)
			ft_draw_sprite(game, siz, off, farthest->content);
	}
}
