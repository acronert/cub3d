/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:39:22 by alex              #+#    #+#             */
/*   Updated: 2024/02/27 17:00:37 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*ft_backtrack(t_list *start)
{
	t_list	*last;
	t_list	*previous;

	previous = start;
	last = ft_lstlast(start);
	while (previous->next && previous->next != last)
		previous = previous->next;
	previous->next = NULL;
	if (last != start)
		ft_lstdelone(last, free);
	else
		return (NULL);
	return (previous);
}

// void	ft_display_map(char **map)
// {
// 	int	x;
// 	int	y;

// 	usleep(50000);
// 	y = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (map[y][x] == WALL)
// 				printf("██");
// 			else if (map[y][x] == SPACE)
// 				printf("  ");
// 			else
// 				printf("%c ", map[y][x]);
// 			x++;
// 		}
// 		printf("\n");
// 		y++;
// 	}
// }

void	ft_move_is_redundant(char **map, t_list **lst, t_list *start,
	int *previous_back)
{
	if (*previous_back == 0 && start->next && start->next->next)
		*lst = ft_backtrack(start);
	map[((t_coord_int *)(*lst)->content)->y]
	[((t_coord_int *)(*lst)->content)->x] = BACKTRACK;
	*lst = ft_backtrack(start);
	*previous_back = 1;
}

void	ft_move_is_valid(char **map, t_list **lst, t_coord_int *dest,
	int *previous_back)
{
	*previous_back = 0;
	map[((t_coord_int *)(*lst)->content)->y]
	[((t_coord_int *)(*lst)->content)->x] = VISITED;
	(*lst)->next = ft_lstnew
		(ft_get_best_move(map, ((t_coord_int *)(*lst)->content), dest));
	*lst = (*lst)->next;
}

t_list	*ft_pathfinder_algo(char **map, t_list *lst, t_coord_int *dest)
{
	t_list	*start;
	int		previous_back;

	previous_back = 0;
	start = lst;
	while (((t_coord_int *)lst->content)->x != dest->x
		|| ((t_coord_int *)lst->content)->y != dest->y)
	{
		if (ft_check_redundancy(map, ((t_coord_int *)lst->content)) == SUCCESS)
			ft_move_is_redundant(map, &lst, start, &previous_back);
		else
			ft_move_is_valid(map, &lst, dest, &previous_back);
		if (!lst)
			return (NULL);
	}
	return (start);
}

t_list	*ft_pathfinder(char **map, t_coord_int *origin, t_coord_int *dest)
{
	t_list	*lst;
	t_list	*tmp;
	char	**map_copy;

	map_copy = ft_arrdup(map);
	if (!map_copy)
		return (NULL);
	ft_change_doors_to_space(map_copy);
	if (ft_check_path_exist(map_copy, origin, dest) == FAILURE)
	{
		ft_free_double_char(map_copy);
		return (NULL);
	}
	lst = ft_lstnew(origin);
	lst = ft_pathfinder_algo(map_copy, lst, dest);
	ft_clean_map(map_copy, BACKTRACK);
	lst = ft_optimize_path(map_copy, lst);
	if (!lst)
		return (NULL);
	tmp = lst->next;
	if (lst)
		free(lst);
	ft_free_double_char(map_copy);
	return (tmp);
}
