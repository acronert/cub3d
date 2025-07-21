/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:49:45 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 13:39:03 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_sprite_angle(t_coord player_pos, t_sprite *sprite)
{
	t_coord	temp;

	temp.x = sprite->pos.x - player_pos.x;
	temp.y = sprite->pos.y - player_pos.y;
	sprite->ray_to_sprite.angle = atanf(temp.y / temp.x);
	if (sprite->pos.x < player_pos.x
		&& sprite->pos.y > player_pos.y)
		sprite->ray_to_sprite.angle += (2 * M_PI);
	else if (sprite->pos.x < player_pos.x
		&& sprite->pos.y < player_pos.y)
		;
	else
		sprite->ray_to_sprite.angle += M_PI;
	sprite->ray_to_sprite.angle += M_PI;
	sprite->ray_to_sprite.angle
		= ft_normalize_angle(sprite->ray_to_sprite.angle);
}

float	ft_find_distance_to_sprite(t_game *game, t_sprite *sprite)
{
	float	a;
	float	b;

	a = (sprite->pos.x - game->player->pos.x)
		* (sprite->pos.x - game->player->pos.x);
	b = (sprite->pos.y - game->player->pos.y)
		* (sprite->pos.y - game->player->pos.y);
	return (sqrtf(a + b));
}

void	ft_check_if_mob_in_sight(t_game *game)
{
	t_inter		*inter;
	t_list		*start;
	t_sprite	*sprite;

	start = game->sprite;
	while (game->sprite)
	{
		sprite = (t_sprite *)game->sprite->content;
		ft_set_sprite_angle(game->player->pos, sprite);
		inter = malloc(sizeof(t_inter));
		if (!inter)
			return ;
		ft_find_ray_intersection(game, &sprite->ray_to_sprite, inter);
		if (!inter)
			return ;
		ft_find_ray_collision(game, &sprite->ray_to_sprite, inter, 0);
		free (inter);
		sprite->distance = ft_find_distance_to_sprite(game, sprite);
		sprite->is_in_sight = 0;
		if (sprite->distance < sprite->ray_to_sprite.length)
			sprite->is_in_sight = 1;
		game->sprite = game->sprite->next;
	}
	game->sprite = start;
}
