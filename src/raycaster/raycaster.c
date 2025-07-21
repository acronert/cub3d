/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:50:49 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 15:52:28 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_set_ray_angle(float player_angle, float ray_delta, int ray_index)
{
	float	ray_angle;

	ray_angle = player_angle + (-(HALF_DISP_WIDTH) + ray_index) * ray_delta;
	ray_angle = ft_normalize_angle(ray_angle);
	return (ray_angle);
}

void	ft_free_rays_bad_malloc(t_ray **ray, int i)
{
	i--;
	while (i >= 0)
	{
		free(ray[i]);
		i--;
	}
	free(ray);
}

t_ray	**ft_create_rays(t_game *game)
{
	t_ray			**ray;
	float			ray_delta;
	register int	i;

	ray = malloc((DISPLAY_W) * sizeof(t_ray *));
	if (!ray)
		return (NULL);
	i = 0;
	while (i < DISPLAY_W)
	{
		ray[i] = malloc(sizeof(t_ray));
		if (!ray[i])
			return (ft_free_rays_bad_malloc(ray, i), NULL);
		i++;
	}
	ray_delta = (FOV * DEG_TO_RAD) / DISPLAY_W;
	i = 0;
	while (i < DISPLAY_W)
	{
		ray[i]->angle = ft_set_ray_angle(game->player->angle, ray_delta, i);
		i++;
	}
	return (ray);
}

void	ft_free_rays(t_ray **ray)
{
	int	i;

	i = -1;
	while (++i < NUMBER_OF_RAYS)
	{
		free(ray[i]);
	}
	free(ray);
}

t_ray	**ft_raycaster(t_game *game)
{
	t_ray			**ray;
	t_inter			*inter;
	register int	i;

	ray = ft_create_rays(game);
	if (!ray)
		return (NULL);
	i = 0;
	while (i < DISPLAY_W)
	{
		inter = malloc(sizeof(t_inter));
		if (!inter)
			return (NULL);
		ft_find_ray_intersection(game, ray[i], inter);
		if (!inter)
			return (NULL);
		ft_find_ray_collision(game, ray[i], inter, 1);
		free (inter);
		i++;
	}
	return (ray);
}
