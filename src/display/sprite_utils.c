/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:48:37 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 13:49:31 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	ft_get_sprite_texture(t_game *game, t_sprite *sprite)
{
	t_texture	texture;

	if (sprite->type == TYPE_THING)
		texture = game->display->the_thing;
	else
		texture = game->display->battery;
	return (texture);
}

int	ft_find_sprite_center(t_game *game, t_list *lst)
{
	t_sprite	*sprite;
	float		ray_delta;
	int			pixel_delta;
	float		angle_diff;

	ray_delta = (FOV * DEG_TO_RAD) / DISPLAY_W;
	sprite = ((t_sprite *)lst->content);
	angle_diff = ft_normalize_angle(sprite->ray_to_sprite.angle
			- game->ray[0]->angle);
	pixel_delta = angle_diff / ray_delta;
	return (pixel_delta);
}

t_list	*ft_find_farthest_sprite(t_list *lst, float *prev_max_dist)
{
	t_list	*start;
	t_list	*farthest;
	float	max_dist;

	max_dist = 0;
	start = lst;
	farthest = NULL;
	while (lst)
	{
		if (((t_sprite *)lst->content)->distance > max_dist
			&& ((t_sprite *)lst->content)->distance < *prev_max_dist)
		{
			max_dist = ((t_sprite *)lst->content)->distance;
			farthest = lst;
		}
		lst = lst->next;
	}
	*prev_max_dist = max_dist;
	lst = start;
	return (farthest);
}
