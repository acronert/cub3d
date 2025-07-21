/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thing_behavior_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:15:35 by acronert          #+#    #+#             */
/*   Updated: 2024/02/22 18:15:57 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_the_thing(char **map, t_coord *pos, t_coord_int *destination)
{
	t_coord	dest;

	dest.x = destination->x + 0.5;
	dest.y = destination->y + 0.5;
	if (pos->x + THING_SPEED < dest.x)
	{
		if (map[(int)pos->y][(int)(pos->x + THING_SPEED)] != WALL)
			pos->x += THING_SPEED;
	}
	else if (pos->x - THING_SPEED > dest.x)
	{
		if (map[(int)pos->y][(int)(pos->x - THING_SPEED)] != WALL)
			pos->x -= THING_SPEED;
	}
	if (pos->y + THING_SPEED < dest.y)
	{
		if (map[(int)(pos->y + THING_SPEED)][(int)pos->x] != WALL)
			pos->y += THING_SPEED;
	}
	else if (pos->y - THING_SPEED > dest.y)
	{
		if (map[(int)(pos->y - THING_SPEED)][(int)pos->x] != WALL)
			pos->y -= THING_SPEED;
	}
}

t_list	*ft_del_current_node(t_sprite *thing, t_list *path)
{
	t_list	*tmp;

	if ((int)thing->pos.x == ((t_coord_int *)path->content)->x
		&& (int)thing->pos.y == ((t_coord_int *)path->content)->y)
	{
		tmp = path->next;
		ft_lstdelone(path, free);
		path = tmp;
	}
	return (path);
}

t_coord_int	ft_get_destination(t_game *game, t_coord_int origin)
{
	t_coord_int	destination;

	destination.x = 0;
	destination.y = 0;
	if (game->pursuit != 0)
	{
		destination.x = game->player->pos.x;
		destination.y = game->player->pos.y;
	}
	else
	{
		while (ft_check_path_exist(game->map, &origin, &destination) == FAILURE)
		{
			destination.x = rand() % (game->map_size.x - 1) + 1;
			destination.y = rand() % (game->map_size.y - 1) + 1;
		}
	}
	return (destination);
}
