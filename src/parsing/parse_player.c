/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:45:04 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 14:45:14 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player	*ft_set_player(char direction, t_coord_int pos)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	if (direction == 'E')
		player->angle = 2 * M_PI;
	else if (direction == 'S')
		player->angle = M_PI / 2;
	else if (direction == 'W')
		player->angle = M_PI;
	else if (direction == 'N')
		player->angle = 3 * M_PI / 2;
	player->pos.x = (float)pos.x + 0.5;
	player->pos.y = (float)pos.y + 0.5;
	player->pitch = 0;
	return (player);
}

int	ft_check_map_player_pos(t_game *game)
{
	t_coord_int	pos;
	int			found_player;

	found_player = 0;
	pos.y = -1;
	while (game->map[++pos.y])
	{
		pos.x = -1;
		while (game->map[pos.y][++pos.x])
		{
			if (ft_is_charset(game->map[pos.y][pos.x], "NSEW"))
			{
				if (found_player)
					return (FAILURE);
				found_player = 1;
				game->player = ft_set_player(game->map[pos.y][pos.x], pos);
				game->map[pos.y][pos.x] = SPACE;
			}
		}
	}
	if (!found_player)
		return (FAILURE);
	return (SUCCESS);
}
