/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <mshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:00:56 by acronert          #+#    #+#             */
/*   Updated: 2024/02/28 15:35:53 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord_int	ft_find_direction(t_coord_int *current, t_coord_int *dest)
{
	t_coord_int	dir;

	dir.x = 0;
	dir.y = 0;
	if (current->x < dest->x)
		dir.x = 1;
	else if (current->x > dest->x)
		dir.x = -1;
	if (current->y < dest->y)
		dir.y = 1;
	else if (current->y > dest->y)
		dir.y = -1;
	return (dir);
}

t_coord_int	*ft_get_best_move_2(char **map, t_coord_int *new_pos,
	t_coord_int dir)
{
	if (dir.y == 0)
	{
		if (map[new_pos->y][new_pos->x + dir.x] == SPACE)
		{
			new_pos->x += dir.x;
			return (new_pos);
		}
		dir.y = 1;
	}
	if (map[new_pos->y][new_pos->x + dir.x] == SPACE)
		new_pos->x += dir.x;
	else if (map[new_pos->y + dir.y][new_pos->x] == SPACE)
		new_pos->y += dir.y;
	else if (map[new_pos->y][new_pos->x - dir.x] == SPACE)
		new_pos->x += -dir.x;
	else if (map[new_pos->y - dir.y][new_pos->x] == SPACE)
		new_pos->y += -dir.y;
	return (new_pos);
}

t_coord_int	*ft_get_best_move(char **map, t_coord_int *pos, t_coord_int *dest)
{
	t_coord_int	dir;
	t_coord_int	*new_pos;

	new_pos = malloc(sizeof(t_coord_int));
	if (!new_pos)
		return (NULL);
	new_pos->x = pos->x;
	new_pos->y = pos->y;
	dir = ft_find_direction(pos, dest);
	if (dir.x == 0)
	{
		if (map[new_pos->y + dir.y][new_pos->x] == SPACE)
		{
			new_pos->y += dir.y;
			return (new_pos);
		}
		dir.x = 1;
	}
	return (ft_get_best_move_2(map, new_pos, dir));
}

int	ft_check_path_exist(char **map, t_coord_int *origin, t_coord_int *dest)
{
	ft_floodfill(map, origin->x, origin->y, '$');
	if (map[dest->y][dest->x] != '$')
	{
		ft_clean_map(map, '$');
		return (FAILURE);
	}
	ft_clean_map(map, '$');
	return (SUCCESS);
}

char	**ft_arrdup(char **arr)
{
	int		i;
	int		len;
	char	**copy;

	len = ft_arrlen(arr);
	copy = malloc((len + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	copy[len] = NULL;
	i = -1;
	while (arr[++i])
	{
		copy[i] = ft_strdup(arr[i]);
		if (!copy[i])
		{
			while (i > 0)
			{
				i--;
				free(copy[i]);
			}
			free(copy);
			return (NULL);
		}
	}
	return (copy);
}
