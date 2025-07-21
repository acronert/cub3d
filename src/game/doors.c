/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:47:53 by acronert          #+#    #+#             */
/*   Updated: 2024/02/22 17:48:24 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_open_doors(t_game *game)
{
	t_list	*start;

	start = game->door;
	while (game->door)
	{
		if (((t_door *)game->door->content)->is_opening == 1)
		{
			((t_door *)game->door->content)->open_state += 0.05;
			if (((t_door *)game->door->content)->open_state >= 0.95)
			{
				((t_door *)game->door->content)->open_state = 0.95;
				((t_door *)game->door->content)->is_opening = 0;
			}
		}
		else if (((t_door *)game->door->content)->is_opening == -1)
		{
			((t_door *)game->door->content)->open_state -= 0.05;
			if (((t_door *)game->door->content)->open_state <= 0)
				((t_door *)game->door->content)->open_state = 0;
			if (((t_door *)game->door->content)->open_state <= 0)
				((t_door *)game->door->content)->is_opening = 0;
		}
		game->door = game->door->next;
	}
	game->door = start;
}

void	ft_set_door_as_opening(t_game *game, t_coord_int door_pos)
{
	t_list	*start;
	t_list	*lst;

	lst = game->door;
	start = lst;
	while (lst)
	{
		if (((t_door *)lst->content)->pos.x == door_pos.x
			&& ((t_door *)lst->content)->pos.y == door_pos.y)
		{
			if (((t_door *)lst->content)->open_state > 0)
				((t_door *)lst->content)->is_opening = -1;
			else
				((t_door *)lst->content)->is_opening = 1;
		}
		lst = lst->next;
	}
	game->door = start;
}

t_coord_int	ft_find_door_to_open(t_game *game)
{
	t_coord		pos;
	t_coord_int	door_pos;

	pos.x = game->player->pos.x + cosf(game->player->angle) * 1;
	pos.y = game->player->pos.y + sinf(game->player->angle) * 1;
	door_pos.x = (int)pos.x;
	door_pos.y = (int)pos.y;
	if (game->map[door_pos.y][door_pos.x] == DOOR_VER
		|| game->map[door_pos.y][door_pos.x] == DOOR_HOR)
		return (door_pos);
	door_pos.x = -1;
	door_pos.y = -1;
	return (door_pos);
}
