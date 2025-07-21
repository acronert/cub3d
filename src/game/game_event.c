/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <mshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:19:55 by acronert          #+#    #+#             */
/*   Updated: 2024/02/28 15:26:50 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_if_next_to_exit(t_game *game)
{
	t_coord_int	pos;

	pos.x = (int)game->player->pos.x;
	pos.y = (int)game->player->pos.y;
	if (game->map[pos.y][pos.x + 1] == EXIT_WALL
		|| game->map[pos.y][pos.x - 1] == EXIT_WALL
		|| game->map[pos.y + 1][pos.x] == EXIT_WALL
		|| game->map[pos.y - 1][pos.x] == EXIT_WALL)
		return (SUCCESS);
	return (FAILURE);
}

void	ft_check_game_over(t_game *game)
{
	t_sprite	*sprite;

	sprite = (t_sprite *)game->sprite->content;
	if (ft_check_if_next_to_exit(game) == SUCCESS)
	{
		printf("YOU FOUND THE EXIT AND ESCAPED TO A BETTER LIFE\n");
		ft_exit(game);
	}
	else if (sprite->distance <= 1)
	{
		printf("YOU GOT CAUGHT BY THE THING AND DIED IN TERRIBLE PAIN\n");
		ft_exit(game);
	}
}

void	ft_update_game(t_game *game)
{
	t_coord_int	door_pos;

	if (game->space_bar == 1)
	{
		door_pos = ft_find_door_to_open(game);
		ft_set_door_as_opening(game, door_pos);
		game->space_bar = 0;
	}
	ft_drain_battery(game);
	ft_open_doors(game);
	ft_check_if_mob_in_sight(game);
	ft_pick_battery(game);
	if (((t_sprite *)game->sprite->content)->is_in_sight)
		ft_flashlight_flicker(game);
	else
		game->flashlight = 1;
	if (game->thing_exist)
		ft_the_thing_behavior(game);
	ft_check_game_over(game);
}

void	ft_game_event(t_game *game)
{
	game->flashlight_offset = ft_flashlight_offset(game->flashlight_offset);
	ft_display(game);
	ft_update_game(game);
}
