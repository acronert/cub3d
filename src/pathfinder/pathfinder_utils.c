/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:56:23 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 17:00:52 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_count_visited_neighbors(char **map, t_coord_int *position)
{
	int	count;

	count = 0;
	if (map[position->y + 1][position->x] == VISITED)
		count++;
	if (map[position->y - 1][position->x] == VISITED)
		count++;
	if (map[position->y][position->x + 1] == VISITED)
		count++;
	if (map[position->y][position->x - 1] == VISITED)
		count++;
	return (count);
}

int	ft_count_possible_moves(char **map, t_coord_int *position)
{
	int	count;

	count = 0;
	if (map[position->y + 1][position->x] == SPACE)
		count++;
	if (map[position->y - 1][position->x] == SPACE)
		count++;
	if (map[position->y][position->x + 1] == SPACE)
		count++;
	if (map[position->y][position->x - 1] == SPACE)
		count++;
	return (count);
}

int	ft_check_redundancy(char **map, t_coord_int *position)
{
	if (ft_count_possible_moves(map, position) == 0
		|| ft_count_visited_neighbors(map, position) > 1)
		return (SUCCESS);
	return (FAILURE);
}

void	ft_clean_map(char **map, char c)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
				map[y][x] = SPACE;
			x++;
		}
		y++;
	}
}

void	ft_change_doors_to_space(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == DOOR_HOR || map[y][x] == DOOR_VER)
				map[y][x] = SPACE;
			x++;
		}
		y++;
	}
}
