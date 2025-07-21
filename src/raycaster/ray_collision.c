/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:16:59 by alex              #+#    #+#             */
/*   Updated: 2024/02/26 16:39:27 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord	ft_calculate_distance_to_intersect(t_game *game, t_inter *inter)
{
	t_coord	distance_to_inter;

	if (0 < inter->hor.x && inter->hor.x < game->map_size.x)
		distance_to_inter.x = sqrtf((inter->hor.x - game->player->pos.x)
				* (inter->hor.x - game->player->pos.x)
				+ (inter->hor.y - game->player->pos.y)
				* (inter->hor.y - game->player->pos.y));
	else
		distance_to_inter.x = game->map_size.y * game->map_size.x;
	if (0 < inter->ver.y && inter->ver.y < game->map_size.y)
		distance_to_inter.y = sqrtf((inter->ver.x - game->player->pos.x)
				* (inter->ver.x - game->player->pos.x)
				+ (inter->ver.y - game->player->pos.y)
				* (inter->ver.y - game->player->pos.y));
	else
		distance_to_inter.y = game->map_size.y * game->map_size.x;
	return (distance_to_inter);
}

int	ft_hor_collision(t_game *game, t_ray *ray, t_inter *inter, int a_correction)
{
	t_coord_int	grid;
	float		angle;

	angle = game->player->angle;
	if (a_correction == 0)
		angle = ray->angle;
	grid.x = floorf(inter->hor.x);
	grid.y = inter->hor.y + (inter->tile_step.y -1) / 2;
	if (game->map[grid.y][grid.x] == WALL
		|| game->map[grid.y][grid.x] == EXIT_WALL)
	{
		if (game->map[grid.y][grid.x] == WALL)
			ray->target_type = TARGET_TYPE_WALL;
		if (game->map[grid.y][grid.x] == EXIT_WALL)
			ray->target_type = TARGET_TYPE_EXIT;
		return (ft_hor_collision_wall(game, ray, inter, angle));
	}
	else if (game->map[grid.y][grid.x] == DOOR_HOR)
		return (ft_hor_collision_door(game, ray, inter, angle));
	return (FAILURE);
}

int	ft_ver_collision(t_game *game, t_ray *ray, t_inter *inter, int a_correction)
{
	t_coord_int	grid;
	float		angle;

	angle = game->player->angle;
	if (a_correction == 0)
		angle = ray->angle;
	grid.x = inter->ver.x + (inter->tile_step.x -1) / 2;
	grid.y = floorf(inter->ver.y);
	if (game->map[grid.y][grid.x] == WALL
		|| game->map[grid.y][grid.x] == EXIT_WALL)
	{
		if (game->map[grid.y][grid.x] == WALL)
			ray->target_type = TARGET_TYPE_WALL;
		if (game->map[grid.y][grid.x] == EXIT_WALL)
			ray->target_type = TARGET_TYPE_EXIT;
		return (ft_ver_collision_wall(game, ray, inter, angle));
	}
	else if (game->map[grid.y][grid.x] == DOOR_VER)
		return (ft_ver_collision_door(game, ray, inter, angle));
	return (FAILURE);
}

void	ft_find_ray_collision(t_game *game, t_ray *ray, t_inter *inter,
	int a_correction)
{
	t_coord	distance_to_inter;

	while (1)
	{
		distance_to_inter = ft_calculate_distance_to_intersect(game, inter);
		if (distance_to_inter.x <= distance_to_inter.y)
		{
			if (ft_hor_collision(game, ray, inter, a_correction) == SUCCESS)
				return ;
			inter->hor.x += inter->step.x;
			inter->hor.y += inter->tile_step.y;
		}
		else if (distance_to_inter.x > distance_to_inter.y)
		{
			if (ft_ver_collision(game, ray, inter, a_correction) == SUCCESS)
				return ;
			inter->ver.x += inter->tile_step.x;
			inter->ver.y += inter->step.y;
		}
	}
}
