/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:30:17 by alex              #+#    #+#             */
/*   Updated: 2024/02/27 15:02:58 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_fill(char **map, int x, int y, t_color c)
{
	if (!map)
		return ;
	if (ft_arrlen(map) < y)
		return ;
	if (ft_strlen_int(map[y]) < x)
		return ;
	if (map[y][x] == c.red)
	{
		map[y][x] = c.green;
		ft_fill(map, x + 1, y, c);
		ft_fill(map, x - 1, y, c);
		ft_fill(map, x, y + 1, c);
		ft_fill(map, x, y - 1, c);
	}
}

char	**ft_floodfill(char **map, int x, int y, char new_c)
{
	t_color	c;

	c.green = new_c;
	if (!map)
		return (NULL);
	if (ft_arrlen(map) < y)
		return (NULL);
	if (ft_strlen_int(map[y]) < x)
		return (NULL);
	c.red = map[y][x];
	ft_fill(map, x, y, c);
	return (map);
}
