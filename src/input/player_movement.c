/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:09:22 by alex              #+#    #+#             */
/*   Updated: 2024/02/27 15:45:57 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_player_move(t_game *game, t_player *player, int x_dir, int i)
{
	t_ray	*ray;
	t_inter	inter;

	ray = malloc(3 * sizeof(t_ray));
	if (!ray)
		return (FAILURE);
	while (++i < 3)
	{
		ray[i].angle = player->angle - 30 * DEG_TO_RAD + (i * 30 * DEG_TO_RAD);
		if (x_dir == -1)
			ray[i].angle = ray[i].angle + M_PI;
		ray[i].angle = ft_normalize_angle(ray[i].angle);
		ft_find_ray_intersection(game, &ray[i], &inter);
		ft_find_ray_collision(game, &ray[i], &inter, 1);
		if (ray[i].target_type == TARGET_TYPE_DOOR)
			ray[i].length += 0.7 * -x_dir;
		if (x_dir == -1)
			ray[i].length *= -1;
		if (ray[i].length < MOVE_SPEED * 2)
			return (free(ray), FAILURE);
	}
	player->pos.x = player->pos.x + x_dir * cosf(player->angle) * MOVE_SPEED;
	player->pos.y = player->pos.y + x_dir * sinf(player->angle) * MOVE_SPEED;
	return (free(ray), SUCCESS);
}

int	ft_player_move_side(t_game *game, t_player *ply, int y_dir)
{
	t_ray	*ray;
	t_inter	inter;
	int		i;

	ray = malloc(3 * sizeof(t_ray));
	if (!ray)
		return (FAILURE);
	i = -1;
	while (++i < 3)
	{
		ray[i].angle = ply->angle + (M_PI / 2) - 30 * DEG_TO_RAD
			+ (i * 30 * DEG_TO_RAD);
		if (y_dir == -1)
			ray[i].angle = ray[i].angle + M_PI;
		ray[i].angle = ft_normalize_angle(ray[i].angle);
		ft_find_ray_intersection(game, &ray[i], &inter);
		ft_find_ray_collision(game, &ray[i], &inter, 0);
		if (ray[i].target_type == TARGET_TYPE_DOOR)
			ray[i].length += -0.7 * abs(y_dir);
		if (ray[i].length < MOVE_SPEED * 2)
			return (free(ray), FAILURE);
	}
	ply->pos.x = ply->pos.x + y_dir * y_dir * cosf(ray[1].angle) * MOVE_SPEED ;
	ply->pos.y = ply->pos.y + y_dir * y_dir * sinf(ray[1].angle) * MOVE_SPEED ;
	return (free(ray), SUCCESS);
}

void	ft_player_rotate(t_game *game, int dir)
{
	game->player->angle += dir * TURN_SPEED;
	game->player->angle = ft_normalize_angle(game->player->angle);
	game->flashlight_offset.x += dir;
}

void	ft_player_pitch(t_game *game, int dir)
{
	game->player->pitch -= dir / 2;
	if (game->player->pitch > HALF_DISP_HEIGHT)
		game->player->pitch = HALF_DISP_HEIGHT;
	else if (game->player->pitch < -HALF_DISP_HEIGHT)
		game->player->pitch = -HALF_DISP_HEIGHT;
	game->flashlight_offset.y += dir;
}
