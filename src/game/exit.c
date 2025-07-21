/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <mshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:27:15 by alex              #+#    #+#             */
/*   Updated: 2024/02/28 15:34:10 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_destroy_constant_images(t_display *dis)
{
	if (dis->exit.img)
		mlx_destroy_image(dis->mlx, dis->exit.img);
	if (dis->flashlight.img)
		mlx_destroy_image(dis->mlx, dis->flashlight.img);
	if (dis->phone.img)
		mlx_destroy_image(dis->mlx, dis->phone.img);
	if (dis->overlay.img)
		mlx_destroy_image(dis->mlx, dis->overlay.img);
	if (dis->minimap.img)
		mlx_destroy_image(dis->mlx, dis->minimap.img);
}

void	ft_destroy_images(t_display *dis)
{
	if (dis->wall_n.img)
		mlx_destroy_image(dis->mlx, dis->wall_n.img);
	if (dis->wall_s.img)
		mlx_destroy_image(dis->mlx, dis->wall_s.img);
	if (dis->wall_e.img)
		mlx_destroy_image(dis->mlx, dis->wall_e.img);
	if (dis->wall_w.img)
		mlx_destroy_image(dis->mlx, dis->wall_w.img);
	if (dis->door.img)
		mlx_destroy_image(dis->mlx, dis->door.img);
	if (dis->the_thing.img)
		mlx_destroy_image(dis->mlx, dis->the_thing.img);
	if (dis->skybox.img)
		mlx_destroy_image(dis->mlx, dis->skybox.img);
	if (dis->battery.img)
		mlx_destroy_image(dis->mlx, dis->battery.img);
}

void	ft_free_display_path(t_display *display)
{
	if (display->wall_n.path)
		free(display->wall_n.path);
	if (display->wall_s.path)
		free(display->wall_s.path);
	if (display->wall_e.path)
		free(display->wall_e.path);
	if (display->wall_w.path)
		free(display->wall_w.path);
	if (display->door.path)
		free(display->door.path);
	if (display->the_thing.path)
		free(display->the_thing.path);
	if (display->skybox.path)
		free(display->skybox.path);
	if (display->battery.path)
		free(display->battery.path);
	if (display->phone.path)
		free(display->phone.path);
	if (display->overlay.path)
		free(display->overlay.path);
	if (display->flashlight.path)
		free(display->flashlight.path);
	if (display->exit.path)
		free(display->exit.path);
}

void	ft_free_game_display(t_game *game)
{
	t_display	*dis;

	if (game->display)
	{
		dis = game->display;
		ft_destroy_images(dis);
		ft_destroy_constant_images(dis);
		ft_free_display_path(dis);
		if (dis->img.img)
			mlx_destroy_image(dis->mlx, dis->img.img);
		if (dis->win)
			mlx_destroy_window(dis->mlx, dis->win);
		if (dis->mlx)
		{
			mlx_destroy_display(dis->mlx);
			free(dis->mlx);
		}
		if (dis)
			free(dis);
	}
}

int	ft_exit(t_game *game)
{
	ft_free_game_display(game);
	if (game->map)
		ft_free_double_char(game->map);
	ft_lstclear(&game->sprite, free);
	ft_lstclear(&game->door, free);
	if (game->thing_path)
		ft_lstclear(&game->thing_path, free);
	if (game->fps)
		free(game->fps);
	if (game->player)
		free(game->player);
	free(game);
	exit(0);
}
