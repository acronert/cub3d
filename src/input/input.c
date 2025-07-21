/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 12:29:13 by alex              #+#    #+#             */
/*   Updated: 2024/02/27 16:32:47 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_press(int key, t_game *game)
{
	if (key == MOVE_RIGHT)
		game->key_pressed.m_right = 1;
	else if (key == MOVE_LEFT)
		game->key_pressed.m_left = 1;
	else if (key == MOVE_FORWARD)
		game->key_pressed.m_up = 1;
	else if (key == MOVE_BACKWARD)
		game->key_pressed.m_down = 1;
	else if (key == ROTATE_RIGHT)
		game->key_pressed.r_right = 1;
	else if (key == ROTATE_LEFT)
		game->key_pressed.r_left = 1;
	else if (key == ROTATE_UP)
		game->key_pressed.r_up = 1;
	else if (key == ROTATE_DOWN)
		game->key_pressed.r_down = 1;
	else if (key == EXIT_KEY)
		ft_exit(game);
	else if (key == M_KEY)
		game->mini_map = !game->mini_map;
	else if (key == C_KEY)
		game->sky = !game->sky;
	else if (key == SPACE_BAR)
		game->space_bar = !game->space_bar;
	return (0);
}
	// else if (key == PLUS_KEY) // TESTING PURPOSE
	// 	game->battery_lvl += 0.1;
	// else if (key == MINUS_KEY) // TESTING PURPOSE
	// 	game->battery_lvl -= 0.1;

int	ft_key_release(int key, t_game *game)
{
	if (key == MOVE_RIGHT)
		game->key_pressed.m_right = 0;
	else if (key == MOVE_LEFT)
		game->key_pressed.m_left = 0;
	else if (key == MOVE_FORWARD)
		game->key_pressed.m_up = 0;
	else if (key == MOVE_BACKWARD)
		game->key_pressed.m_down = 0;
	else if (key == ROTATE_RIGHT)
		game->key_pressed.r_right = 0;
	else if (key == ROTATE_LEFT)
		game->key_pressed.r_left = 0;
	else if (key == ROTATE_UP)
		game->key_pressed.r_up = 0;
	else if (key == ROTATE_DOWN)
		game->key_pressed.r_down = 0;
	return (0);
}

int	ft_loop(t_game *game)
{	
	if (game->key_pressed.r_right)
		ft_player_rotate(game, 70);
	if (game->key_pressed.m_up)
		ft_player_move(game, game->player, 1, -1);
	if (game->key_pressed.r_left)
		ft_player_rotate(game, -70);
	if (game->key_pressed.m_down)
		ft_player_move(game, game->player, -1, -1);
	if (game->key_pressed.m_left)
		ft_player_move_side(game, game->player, -1);
	if (game->key_pressed.m_right)
		ft_player_move_side(game, game->player, 1);
	if (game->key_pressed.r_up)
		ft_player_pitch(game, -60);
	if (game->key_pressed.r_down)
		ft_player_pitch(game, 60);
	ft_game_event(game);
	return (0);
}

int	ft_mouse(int x, int y, t_game *game)
{
	t_coord_int	mouse_mvmt;

	(void)y;
	mouse_mvmt.x = (x - (HALF_DISP_WIDTH));
	mouse_mvmt.y = (y - (HALF_DISP_HEIGHT));
	if (mouse_mvmt.x != 0)
	{
		ft_player_rotate(game, mouse_mvmt.x);
	}
	if (mouse_mvmt.y != 0)
	{
		ft_player_pitch(game, mouse_mvmt.y);
	}
	mlx_mouse_move(game->display->mlx, game->display->win, HALF_DISP_WIDTH,
		HALF_DISP_HEIGHT);
	return (0);
}

void	ft_input(t_game *game)
{
	mlx_mouse_hide(game->display->mlx, game->display->win);
	mlx_mouse_move(game->display->mlx, game->display->win, HALF_DISP_WIDTH,
		HALF_DISP_HEIGHT);
	mlx_hook(game->display->win, 2, 1, ft_key_press, (void *)game);
	mlx_hook(game->display->win, 3, 1L << 1, ft_key_release, (void *)game);
	mlx_hook(game->display->win, 6, 1L << 6, ft_mouse, (void *)game);
	mlx_loop_hook(game->display->mlx, ft_loop, (void *)game);
	mlx_hook(game->display->win, 17, 0L, ft_exit, (void *)game);
	mlx_loop(game->display->mlx);
}
