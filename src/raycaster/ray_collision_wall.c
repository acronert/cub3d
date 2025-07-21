/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:42:26 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 15:55:41 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_ver_collision_wall(t_game *game, t_ray *ray, t_inter *inter, float angle)
{
	if (inter->tile_step.x == 1)
		ray->target_orientation = ORIENTATION_W;
	else
		ray->target_orientation = ORIENTATION_E;
	ray->target_column = inter->ver.y - floorf(inter->ver.y);
	ray->length = (inter->ver.x - game->player->pos.x) * cosf(angle)
		+ (inter->ver.y - game->player->pos.y) * (sinf(angle));
	return (SUCCESS);
}

int	ft_hor_collision_wall(t_game *game, t_ray *ray, t_inter *inter, float angle)
{
	if (inter->tile_step.y == 1)
		ray->target_orientation = ORIENTATION_N;
	else
		ray->target_orientation = ORIENTATION_S;
	ray->target_column = inter->hor.x - floorf(inter->hor.x);
	ray->length = (inter->hor.x - game->player->pos.x) * cosf(angle)
		+ (inter->hor.y - game->player->pos.y) * (sinf(angle));
	return (SUCCESS);
}
