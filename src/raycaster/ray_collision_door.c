/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision_door.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:54:27 by acronert          #+#    #+#             */
/*   Updated: 2024/02/22 11:50:39 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_get_door_open_state(t_game *game, int pos_x, int pos_y)
{
	t_list	*lst;

	lst = game->door;
	while (lst)
	{
		if (((t_door *)lst->content)->pos.x == pos_x
			&& ((t_door *)lst->content)->pos.y == pos_y)
			return (((t_door *)lst->content)->open_state);
		lst = lst->next;
	}
	return (0);
}

int	ft_hor_collision_door(t_game *game, t_ray *ray, t_inter *inter, float angle)
{
	float	opening_state;

	if (-0.5 < (inter->hor.y - inter->ver.y)
		&& (inter->hor.y - inter->ver.y) < 0.5)
		return (FAILURE);
	ray->target_type = TARGET_TYPE_DOOR;
	inter->hor.x += inter->step.x / 2;
	inter->hor.y += inter->tile_step.y / 2;
	ray->target_column = inter->hor.x - floorf(inter->hor.x);
	if (inter->tile_step.y == 1)
		ray->target_orientation = ORIENTATION_N;
	else
		ray->target_orientation = ORIENTATION_S;
	opening_state = ft_get_door_open_state(game, inter->hor.x, inter->hor.y);
	if (ray->target_column < opening_state)
	{
		inter->hor.x -= inter->step.x / 2;
		inter->hor.y -= inter->tile_step.y / 2;
		return (FAILURE);
	}
	ray->target_column = inter->hor.x - floorf(inter->hor.x) - opening_state;
	ray->length = (inter->hor.x - game->player->pos.x) * cosf(angle)
		+ (inter->hor.y - game->player->pos.y) * (sinf(angle));
	return (SUCCESS);
}

int	ft_ver_collision_door(t_game *game, t_ray *ray, t_inter *inter, float angle)
{
	float	opening_state;

	if (-0.5 < (inter->ver.x - inter->hor.x)
		&& (inter->ver.x - inter->hor.x) < 0.5)
		return (FAILURE);
	ray->target_type = TARGET_TYPE_DOOR;
	inter->ver.x += inter->tile_step.x / 2;
	inter->ver.y += inter->step.y / 2;
	ray->target_column = inter->ver.y - floorf(inter->ver.y);
	opening_state = ft_get_door_open_state(game, inter->ver.x, inter->ver.y);
	if (inter->tile_step.x == 1)
		ray->target_orientation = ORIENTATION_W;
	else
		ray->target_orientation = ORIENTATION_E;
	if (ray->target_column < opening_state)
	{
		inter->ver.x -= inter->tile_step.x / 2;
		inter->ver.y -= inter->step.y / 2;
		return (FAILURE);
	}
	ray->target_column = inter->ver.y - floorf(inter->ver.y) - opening_state;
	ray->length = (inter->ver.x - game->player->pos.x) * cosf(angle)
		+ (inter->ver.y - game->player->pos.y) * (sinf(angle));
	return (SUCCESS);
}
