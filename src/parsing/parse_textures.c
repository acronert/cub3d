/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <mshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:18:26 by acronert          #+#    #+#             */
/*   Updated: 2024/02/28 15:35:27 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_texture_path(t_texture *texture, char *path)
{
	if (!path)
		return (FAILURE);
	if (ft_strncmp(ft_strrchr(path, '.'), ".xpm", 5))
		return (FAILURE);
	if (access(path, F_OK | R_OK))
		return (FAILURE);
	if (texture->path)
		return (FAILURE);
	texture->path = ft_strdup(path);
	if (!texture->path)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_check_texture(t_display *display, char *line)
{
	int	i;

	if (!ft_strncmp(line, "NO ", 3))
		i = ft_init_texture_path(&display->wall_n, line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		i = ft_init_texture_path(&display->wall_s, line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		i = ft_init_texture_path(&display->wall_w, line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		i = ft_init_texture_path(&display->wall_e, line + 3);
	else if (!ft_strncmp(line, "DO ", 3))
		i = ft_init_texture_path(&display->door, line + 3);
	else if (!ft_strncmp(line, "SK ", 3))
		i = ft_init_texture_path(&display->skybox, line + 3);
	else if (!ft_strncmp(line, "TH ", 3))
		i = ft_init_texture_path(&display->the_thing, line + 3);
	else if (!ft_strncmp(line, "BA ", 3))
		i = ft_init_texture_path(&display->battery, line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		i = ft_init_color(&display->floor_color, line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		i = ft_init_color(&display->ceiling_color, line + 2);
	else
		i = FAILURE;
	return (i);
}

int	ft_check_missing_textures(t_display *display)
{
	if (!display->wall_n.path
		|| !display->wall_s.path
		|| !display->wall_e.path
		|| !display->wall_w.path
		|| !display->door.path
		|| !display->the_thing.path
		|| !display->skybox.path
		|| !display->battery.path
		|| !display->phone.path
		|| !display->overlay.path
		|| !display->flashlight.path
		|| !display->exit.path
		|| !display->floor_color.set
		|| !display->ceiling_color.set)
		return (FAILURE);
	return (SUCCESS);
}

void	ft_init_textures(t_display *display)
{
	display->wall_n.path = NULL;
	display->wall_s.path = NULL;
	display->wall_e.path = NULL;
	display->wall_w.path = NULL;
	display->door.path = NULL;
	display->skybox.path = NULL;
	display->the_thing.path = NULL;
	display->battery.path = NULL;
	display->exit.path = ft_strdup("./textures/exit.xpm");
	display->phone.path = ft_strdup("./textures/phone.xpm");
	display->overlay.path = ft_strdup("./textures/camera_overlay.xpm");
	display->flashlight.path = ft_strdup("./textures/flashlight.xpm");
	display->ceiling_color.set = 0;
	display->floor_color.set = 0;
}

t_display	*ft_parse_texture(t_list **lst)
{
	t_display	*display;
	t_list		*start;

	if (!lst)
		return (NULL);
	display = malloc(sizeof(t_display));
	if (!display)
		return (NULL);
	ft_init_textures(display);
	start = *lst;
	while (*lst)
	{
		if (ft_check_texture(display, (*lst)->content) == FAILURE)
		{
			*lst = start;
			ft_free_display_path(display);
			return (free(display), NULL);
		}
		*lst = (*lst)->next;
	}
	ft_lstclear(&start, free);
	if (ft_check_missing_textures(display) == FAILURE)
		return (ft_free_display_path(display), free(display), NULL);
	return (display);
}
