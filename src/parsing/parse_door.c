/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:42:29 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 14:42:58 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_valid_door(char **map, t_coord_int pos)
{
	if (map[pos.y][pos.x] == DOOR_HOR && map[pos.y][pos.x - 1] == WALL
					&& map[pos.y][pos.x + 1] == WALL)
		return (SUCCESS);
	else if (map[pos.y][pos.x] == DOOR_VER && map[pos.y - 1][pos.x] == WALL
		&& map[pos.y + 1][pos.x] == WALL)
		return (SUCCESS);
	return (FAILURE);
}

int	ft_create_door(t_list **lst, char **map, t_coord_int pos)
{
	t_door		*door;

	if (ft_check_valid_door(map, pos) == FAILURE)
		return (ft_lstclear(lst, free), FAILURE);
	door = malloc(sizeof(t_door));
	if (!door)
		return (ft_lstclear(lst, free), FAILURE);
	door->pos = pos;
	door->open_state = 0;
	door->is_opening = 0;
	ft_lstadd_back(lst, ft_lstnew(door));
	return (SUCCESS);
}

int	ft_init_doors(char **map, t_list **lst)
{
	t_coord_int	pos;

	pos.y = -1;
	while (map[++pos.y])
	{
		pos.x = -1;
		while (map[pos.y][++pos.x])
		{
			if (map[pos.y][pos.x] == DOOR_HOR || map[pos.y][pos.x] == DOOR_VER)
			{
				if (ft_create_door(lst, map, pos) == FAILURE)
					return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}
