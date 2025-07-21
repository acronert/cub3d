/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <mshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:24:57 by acronert          #+#    #+#             */
/*   Updated: 2024/02/28 14:52:14 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_texture	ft_init_texture(void *mlx, t_texture tx)
// {
// 	tx.img = mlx_xpm_file_to_image(mlx, tx.path, &tx.size.x, &tx.size.y);
// 	tx.bpp = BPP;
// 	tx.line_size = 4 * tx.size.x;
// 	tx.buf = mlx_get_data_addr(tx.img, &tx.bpp, &tx.line_size,
// 			&tx.endian);
// 	return (tx);
// }

t_texture	ft_init_texture(void *mlx, t_texture tx)
{
	tx.img = mlx_xpm_file_to_image(mlx, tx.path, &tx.size.x, &tx.size.y);
	if (!tx.img)
	{
		tx.bpp = BPP;
		tx.line_size = 4 * tx.size.x;
		tx.buf = NULL;
		return (tx);
	}
	tx.bpp = BPP;
	tx.line_size = 4 * tx.size.x;
	tx.buf = mlx_get_data_addr(tx.img, &tx.bpp, &tx.line_size,
			&tx.endian);
	return (tx);
}

// int	ft_import_constant_textures(t_display *display)
// {
// 	display->flashlight = ft_init_texture(display->mlx, display->flashlight);
// 	if (!display->flashlight.buf)
// 		return (FAILURE);
// 	display->phone = ft_init_texture(display->mlx, display->phone);
// 	if (!display->phone.buf)
// 		return (FAILURE);
// 	display->exit = ft_init_texture(display->mlx, display->exit);
// 	if (!display->exit.buf)
// 		return (FAILURE);
// 	display->overlay = ft_init_texture(display->mlx, display->overlay);
// 	if (!display->overlay.buf)
// 		return (FAILURE);
// 	return (SUCCESS);
// }

// int	ft_import_textures(t_display *display)
// {
// 	display->wall_n = ft_init_texture(display->mlx, display->wall_n);
// 	if (!display->wall_n.buf)
// 		return (FAILURE);
// 	display->wall_e = ft_init_texture(display->mlx, display->wall_e);
// 	if (!display->wall_e.buf)
// 		return (FAILURE);
// 	display->wall_s = ft_init_texture(display->mlx, display->wall_s);
// 	if (!display->wall_s.buf)
// 		return (FAILURE);
// 	display->wall_w = ft_init_texture(display->mlx, display->wall_w);
// 	if (!display->wall_w.buf)
// 		return (FAILURE);
// 	display->door = ft_init_texture(display->mlx, display->door);
// 	if (!display->door.buf)
// 		return (FAILURE);
// 	display->the_thing = ft_init_texture(display->mlx, display->the_thing);
// 	if (!display->the_thing.buf)
// 		return (FAILURE);
// 	display->skybox = ft_init_texture(display->mlx, display->skybox);
// 	if (!display->skybox.buf)
// 		return (FAILURE);
// 	display->battery = ft_init_texture(display->mlx, display->battery);
// 	if (!display->battery.buf)
// 		return (FAILURE);
// 	return (SUCCESS);
// }

int	ft_import_textures(t_display *dis)
{
	dis->wall_n = ft_init_texture(dis->mlx, dis->wall_n);
	dis->wall_e = ft_init_texture(dis->mlx, dis->wall_e);
	dis->wall_s = ft_init_texture(dis->mlx, dis->wall_s);
	dis->wall_w = ft_init_texture(dis->mlx, dis->wall_w);
	dis->door = ft_init_texture(dis->mlx, dis->door);
	dis->the_thing = ft_init_texture(dis->mlx, dis->the_thing);
	dis->skybox = ft_init_texture(dis->mlx, dis->skybox);
	dis->battery = ft_init_texture(dis->mlx, dis->battery);
	dis->flashlight = ft_init_texture(dis->mlx, dis->flashlight);
	dis->phone = ft_init_texture(dis->mlx, dis->phone);
	dis->exit = ft_init_texture(dis->mlx, dis->exit);
	dis->overlay = ft_init_texture(dis->mlx, dis->overlay);
	if (!dis->wall_n.buf ||!dis->wall_e.buf || !dis->wall_s.buf
		|| !dis->wall_w.buf || !dis->door.buf || !dis->the_thing.buf
		|| !dis->skybox.buf || !dis->battery.buf
		|| !dis->flashlight.buf || !dis->phone.buf || !dis->exit.buf
		|| !dis->overlay.buf)
		return (FAILURE);
	return (SUCCESS);
}
