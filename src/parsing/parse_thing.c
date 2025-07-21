/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_thing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:40:56 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 14:41:07 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_set_thing_start(t_list *lst, t_coord_int pos)
{
	t_sprite	*sprite;

	sprite = lst->content;
	sprite->type = TYPE_THING;
	sprite->frame = 0;
	sprite->frame_nb = 10;
	sprite->pos.x = (float)pos.x + 0.5;
	sprite->pos.y = (float)pos.y + 0.5;
	sprite->is_in_sight = 0;
	sprite->ray_to_sprite.angle = 0;
	sprite->ray_to_sprite.length = 0;
	sprite->ray_to_sprite.target_type = 0;
	sprite->ray_to_sprite.target_orientation = 0;
	sprite->ray_to_sprite.target_column = 0;
	sprite->distance = 100;
}

t_list	*ft_calloc_thing(void)
{
	t_list		*lst;
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	sprite->type = TYPE_THING;
	sprite->frame = 0;
	sprite->frame_nb = 10;
	sprite->pos.x = 0;
	sprite->pos.y = 0;
	sprite->is_in_sight = 0;
	sprite->ray_to_sprite.angle = 0;
	sprite->ray_to_sprite.length = 0;
	sprite->ray_to_sprite.target_type = 0;
	sprite->ray_to_sprite.target_orientation = 0;
	sprite->ray_to_sprite.target_column = 0;
	sprite->distance = 100;
	lst = ft_lstnew(sprite);
	return (lst);
}

int	ft_check_map_thing_pos(t_game *game)
{
	t_coord_int	pos;

	game->sprite = ft_calloc_thing();
	if (!game->sprite)
		return (FAILURE);
	game->thing_exist = 0;
	pos.y = -1;
	while (game->map[++pos.y])
	{
		pos.x = -1;
		while (game->map[pos.y][++pos.x])
		{
			if (game->map[pos.y][pos.x] == 'T')
			{
				if (game->thing_exist)
					return (FAILURE);
				game->thing_exist = 1;
				ft_set_thing_start(game->sprite, pos);
				game->map[pos.y][pos.x] = SPACE;
			}
		}
	}
	return (SUCCESS);
}
