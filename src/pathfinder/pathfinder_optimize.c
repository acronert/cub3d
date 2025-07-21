/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder_optimize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:48:18 by acronert          #+#    #+#             */
/*   Updated: 2024/02/22 12:02:24 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_connect_nodes(t_list *origin, t_list *target)
{
	t_list	*start;
	t_list	*tmp;

	start = origin;
	origin = origin->next;
	while (origin != target)
	{
		tmp = origin->next;
		ft_lstdelone(origin, free);
		origin = tmp;
	}
	origin = start;
	origin->next = target;
}

t_list	*ft_find_node(t_list *node, int x, int y)
{
	t_list	*current;

	current = node;
	while (current)
	{
		if (((t_coord_int *)current->content)->x == x
			&& ((t_coord_int *)current->content)->y == y)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

t_list	*ft_find_shortcut(char **map, t_list *current, int x, int y)
{
	int		i;
	t_list	*target;

	i = 1;
	while (map[((t_coord_int *)current->content)->y + (y * i)]
		[((t_coord_int *)current->content)->x + (x * i)] == SPACE)
		i++;
	target = ft_find_node(current,
			((t_coord_int *)current->content)->x + (x * i),
			((t_coord_int *)current->content)->y + (y * i));
	if (target != NULL)
	{
		ft_connect_nodes(current, target);
		return (target);
	}
	return (current);
}

t_list	*ft_remove_straight_lines(t_list *path)
{
	t_list	*current;
	t_list	*target;

	if (!path)
		return (NULL);
	current = path;
	while (current->next)
	{
		target = current;
		while (target->next && (((t_coord_int *)current->content)->x
				== ((t_coord_int *)target->next->content)->x
				|| ((t_coord_int *)current->content)->y
				== ((t_coord_int *)target->next->content)->y))
				target = target->next;
		ft_connect_nodes(current, target);
		current = current->next;
	}
	return (path);
}

t_list	*ft_optimize_path(char **map, t_list *path)
{
	t_list	*current;

	if (!path)
		return (NULL);
	current = path;
	while (current)
	{
		if (map[((t_coord_int *)current->content)->y + 1]
			[((t_coord_int *)current->content)->x] == SPACE)
			current = ft_find_shortcut(map, current, 0, 1);
		if (map[((t_coord_int *)current->content)->y]
			[((t_coord_int *)current->content)->x + 1] == SPACE)
			current = ft_find_shortcut(map, current, 1, 0);
		if (map[((t_coord_int *)current->content)->y - 1]
			[((t_coord_int *)current->content)->x] == SPACE)
			current = ft_find_shortcut(map, current, 0, -1);
		if (map[((t_coord_int *)current->content)->y]
			[((t_coord_int *)current->content)->x - 1] == SPACE)
			current = ft_find_shortcut(map, current, -1, 0);
		current = current->next;
	}
	path = ft_remove_straight_lines(path);
	return (path);
}
