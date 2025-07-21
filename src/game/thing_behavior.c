/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thing_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:35:21 by acronert          #+#    #+#             */
/*   Updated: 2024/02/22 18:17:45 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_thing_get_a_path(t_game *game, t_coord_int origin)
{
	t_coord_int	destination;

	destination = ft_get_destination(game, origin);
	game->thing_path = ft_pathfinder(game->map, &origin, &destination);
	if (!game->thing_path)
		return (FAILURE);
	return (SUCCESS);
}

void	ft_thing_go_straight_to_player(t_game *game, t_coord_int origin)
{
	t_coord_int	destination;
	t_sprite	*thing;

	thing = ((t_sprite *)game->sprite->content);
	game->pursuit = 1;
	destination = ft_get_destination(game, origin);
	ft_move_the_thing(game->map, &thing->pos, &destination);
}

void	ft_thing_check_last_player_pos(t_game *game)
{
	game->pursuit = 2;
	ft_lstclear(&game->thing_path, free);
}

int	ft_the_thing_behavior(t_game *game)
{
	t_sprite	*thing;
	t_coord_int	origin;

	thing = ((t_sprite *)game->sprite->content);
	origin.x = thing->pos.x;
	origin.y = thing->pos.y;
	if (!game->thing_path)
	{
		if (ft_thing_get_a_path(game, origin) == FAILURE)
			return (0);
	}
	if (game->battery_lvl <= 0)
		game->pursuit = 2;
	if (thing->is_in_sight)
		return (ft_thing_go_straight_to_player(game, origin), 0);
	else if (game->pursuit == 1)
		return (ft_thing_check_last_player_pos(game), 0);
	game->thing_path = ft_del_current_node(thing, game->thing_path);
	if (game->thing_path)
		ft_move_the_thing(game->map, &thing->pos,
			(t_coord_int *)game->thing_path->content);
	else if (game->pursuit == 2 && game->battery_lvl > 0)
		game->pursuit = 0;
	return (0);
}

// void	ft_the_thing_behavior(t_game *game)
// {
// 	t_sprite	*thing;
// 	t_coord_int	origin;
// 	t_coord_int	destination;

// 	thing = ((t_sprite *)game->sprite->content);
// 	origin.x = thing->pos.x;
// 	origin.y = thing->pos.y;
// 	if (!game->thing_path)
// 	{
// 		destination = ft_get_destination(game, origin);
// 		game->thing_path = ft_pathfinder(game->map, &origin, &destination);
// 		if (!game->thing_path)
// 			return ;
// 	}
// 	if (game->battery_lvl <= 0)
// 		game->pursuit = 2;
// 	if (thing->is_in_sight)
// 	{
// 		game->pursuit = 1;
// 		destination = ft_get_destination(game, origin);
// 		ft_move_the_thing(game->map, &thing->pos, &destination);
// 		return ;
// 	}
// 	else if (game->pursuit == 1)
// 	{
// 		game->pursuit = 2;
// 		ft_lstclear(&game->thing_path, free);
// 		return ;
// 	}
// 	game->thing_path = ft_del_current_node(thing, game->thing_path);
// 	if (game->thing_path)
// 		ft_move_the_thing(game->map, &thing->pos,
		// (t_coord_int *)game->thing_path->content);
// 	else if (game->pursuit == 2 && game->battery_lvl > 0)
// 		game->pursuit = 0;
// }