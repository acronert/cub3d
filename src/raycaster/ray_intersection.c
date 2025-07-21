/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:07:24 by alex              #+#    #+#             */
/*   Updated: 2024/02/22 11:47:34 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coord	ft_calculate_tile_step(t_ray *ray)
{
	t_coord	tile_step;

	if (ray->angle > 0 && ray->angle <= (M_PI / 2))
	{
		tile_step.x = 1;
		tile_step.y = 1;
	}
	else if (ray->angle > (M_PI / 2) && ray->angle <= M_PI)
	{
		tile_step.x = -1;
		tile_step.y = 1;
	}
	else if (ray->angle > M_PI && ray->angle <= M_PI + (M_PI / 2))
	{
		tile_step.x = -1;
		tile_step.y = -1;
	}
	else
	{
		tile_step.x = 1;
		tile_step.y = -1;
	}
	return (tile_step);
}

float	ft_calculate_tanf(t_ray *ray)
{
	float	relative_angle;

	relative_angle = ray->angle;
	if ((ray->angle > (M_PI / 2) && ray->angle <= M_PI)
		|| (ray->angle > M_PI + (M_PI / 2) && ray->angle <= (2 * M_PI)))
		relative_angle -= (M_PI / 2);
	return (tanf(relative_angle));
}

void	ft_find_ray_intersection(t_game *game, t_ray *ray, t_inter *intr)
{
	t_coord		delta;
	int			token;
	float		tanf;

	delta.x = game->player->pos.x - floorf(game->player->pos.x);
	delta.y = game->player->pos.y - floorf(game->player->pos.y);
	intr->tile_step = ft_calculate_tile_step(ray);
	tanf = ft_calculate_tanf(ray);
	token = ((intr->tile_step.x * intr->tile_step.y) + 1) / 2;
	intr->step.x = intr->tile_step.x * ((tanf * !token + token)
			/ (tanf * token + !token));
	intr->step.y = intr->tile_step.y * ((tanf * token + !token)
			/ (tanf * !token + token));
	intr->hor.x = game->player->pos.x - intr->tile_step.x * (intr->tile_step.y
			* delta.y - ((1 + intr->tile_step.y) / 2))
		* ((tanf * !token + token) / (tanf * token + !token));
	intr->hor.y = game->player->pos.y - intr->tile_step.y * (intr->tile_step.y
			* delta.y - ((1 + intr->tile_step.y) / 2));
	intr->ver.x = game->player->pos.x - intr->tile_step.x * (intr->tile_step.x
			* delta.x - ((1 + intr->tile_step.x) / 2));
	intr->ver.y = game->player->pos.y - intr->tile_step.y * (intr->tile_step.x
			* delta.x - ((1 + intr->tile_step.x) / 2))
		* ((tanf * token + !token) / (tanf * !token + token));
}
