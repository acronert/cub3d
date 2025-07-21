/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:16:48 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 14:46:21 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_map_borders(char **map)
{
	t_coord_int	p;
	t_coord_int	size;

	if (!map)
		return (FAILURE);
	size.y = ft_arrlen(map);
	size.x = ft_strlen(map[0]);
	p.y = -1;
	while (++p.y < size.y)
	{
		p.x = -1;
		while (++p.x < size.x)
		{
			if (!ft_is_charset(map[p.y][p.x], " 14"))
			{
				if (p.y == 0 || p.y == size.y - 1
					|| p.x == 0 || p.x == size.x - 1)
					return (FAILURE);
				else if (map[p.y][p.x + 1] == ' ' || map[p.y][p.x - 1] == ' '
					|| map[p.y + 1][p.x] == ' ' || map[p.y - 1][p.x] == ' ')
					return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

int	ft_check_incorrect_char(t_game *game)
{
	t_coord_int	pos;

	pos.y = -1;
	while (game->map[++pos.y])
	{
		pos.x = -1;
		while (game->map[pos.y][++pos.x])
		{
			if (!ft_is_charset(game->map[pos.y][pos.x], " 01234"))
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	ft_check_map_validity(t_game *game)
{
	if (ft_check_map_borders(game->map) == FAILURE)
		return (FAILURE);
	if (ft_check_map_player_pos(game) == FAILURE)
		return (FAILURE);
	if (ft_check_map_thing_pos(game) == FAILURE)
		return (FAILURE);
	game->sprite = ft_create_batteries(game->map, game->sprite);
	if (ft_init_doors(game->map, &game->door) == FAILURE)
		return (FAILURE);
	if (ft_check_incorrect_char(game) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
