/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_battery.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:46:08 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 14:48:28 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_batteries(t_list **lst, t_sprite *sprite, t_coord_int pos)
{
	sprite->type = TYPE_BATTERY;
	sprite->frame = 0;
	sprite->frame_nb = 60;
	sprite->pos.x = (float)pos.x + 0.5;
	sprite->pos.y = (float)pos.y + 0.5;
	sprite->is_in_sight = 0;
	sprite->ray_to_sprite.angle = 0;
	sprite->ray_to_sprite.length = 0;
	sprite->ray_to_sprite.target_type = 0;
	sprite->ray_to_sprite.target_orientation = 0;
	sprite->ray_to_sprite.target_column = 0;
	sprite->distance = 100;
	ft_lstadd_back(lst, ft_lstnew(sprite));
}

t_list	*ft_create_batteries(char **map, t_list *lst)
{
	t_coord_int	pos;
	t_sprite	*sprite;
	t_list		*start;

	start = lst;
	pos.y = -1;
	while (map[++pos.y])
	{
		pos.x = -1;
		while (map[pos.y][++pos.x])
		{
			if (map[pos.y][pos.x] == 'B')
			{
				sprite = malloc(sizeof(t_sprite));
				if (!sprite)
					return (ft_lstclear(&start, free), NULL);
				ft_init_batteries(&lst, sprite, pos);
				map[pos.y][pos.x] = SPACE;
			}
		}
	}
	return (start);
}
