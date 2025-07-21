/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:49:38 by alex              #+#    #+#             */
/*   Updated: 2024/02/26 18:49:23 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord_int	ft_flashlight_offset(t_coord_int flashlight_offset)
{
	if (flashlight_offset.x > 0)
		flashlight_offset.x = flashlight_offset.x >> 1;
	else if (flashlight_offset.x < 0)
		flashlight_offset.x = flashlight_offset.x >> 1;
	if (flashlight_offset.y > 0)
		flashlight_offset.y = flashlight_offset.y >> 1;
	else if (flashlight_offset.y < 0)
		flashlight_offset.y = flashlight_offset.y >> 1;
	if (flashlight_offset.x > HALF_DISP_WIDTH)
		flashlight_offset.x = HALF_DISP_WIDTH;
	else if (flashlight_offset.x < -HALF_DISP_WIDTH)
		flashlight_offset.x = -HALF_DISP_WIDTH;
	if (flashlight_offset.y > HALF_DISP_HEIGHT)
		flashlight_offset.y = HALF_DISP_HEIGHT;
	else if (flashlight_offset.y < -HALF_DISP_HEIGHT)
		flashlight_offset.y = -HALF_DISP_HEIGHT;
	return (flashlight_offset);
}

void	ft_flashlight(t_game *game, float ray_len, char *buf, t_coord_int pixel)
{
	t_coord		target;
	float		shadow;
	t_texture	texture;

	texture = game->display->flashlight;
	target.x = (float)(pixel.x - ((DISPLAY_W - DISPLAY_H) / 2))
		*((float)texture.size.x / DISPLAY_H);
	target.y = (float)(pixel.y * ((float)texture.size.y / DISPLAY_H));
	target.y += game->flashlight_offset.y;
	target.x += game->flashlight_offset.x;
	ft_normalize_target(&target, &texture);
	shadow = 0;
	if (game->battery_lvl > 0)
		shadow = (game->battery_lvl * 0.4 + 0.2) / (ray_len + 20);
	buf[0] *= 1 + (unsigned char)texture.buf
	[0 + ((int)target.y * texture.size.x + (int)target.x) * 4] * shadow;
	buf[1] *= 1 + (unsigned char)texture.buf
	[1 + ((int)target.y * texture.size.x + (int)target.x) * 4] * shadow;
	buf[2] *= 1 + (unsigned char)texture.buf
	[2 + ((int)target.y * texture.size.x + (int)target.x) * 4] * shadow;
	if (buf[0] < 0 || buf[1] < 0 || buf[2] < 0)
		ft_pixtobuf(buf, 200, 200, 200);
}
