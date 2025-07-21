/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:12:58 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 14:38:21 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*ft_find_map_start(t_list *lst)
{
	t_list	*previous;

	previous = NULL;
	while (lst)
	{
		if (ft_str_ischarset((char *)lst->content, " 14")
			&& (ft_strchr((char *)lst->content, '1')
				|| ft_strchr((char *)lst->content, '4')))
		{
			previous->next = NULL;
			return (lst);
		}
		previous = lst;
		lst = lst->next;
	}
	return (NULL);
}

int	ft_find_map_height(t_list *map_start)
{
	int	count;

	count = 0;
	while (map_start)
	{
		count++;
		map_start = map_start->next;
	}
	return (count);
}

int	ft_find_map_width(t_list *map_start)
{
	int	len;
	int	big_len;

	len = 0;
	big_len = 0;
	while (map_start)
	{
		len = ft_strlen((char *)map_start->content);
		if (len > big_len)
			big_len = len;
		map_start = map_start->next;
	}
	return (big_len);
}

char	**ft_malloc_map(t_list *map_start, int map_height, int map_width)
{
	char	**map;
	int		i;
	int		j;

	map = malloc((map_height + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	map[map_height] = NULL;
	i = 0;
	while (map_start)
	{
		map[i] = malloc((map_width + 1) * sizeof(char));
		if (!map[i])
			return (ft_free_map(map, i), NULL);
		ft_memset(map[i], (int) ' ', map_width);
		map[i][map_width] = '\0';
		j = -1;
		while (map[i][++j] && ((char *)map_start->content)[j])
			map[i][j] = ((char *)map_start->content)[j];
		i++;
		map_start = map_start->next;
	}
	return (map);
}

char	**ft_create_map(t_list *lst)
{
	t_list	*map_start;
	int		map_height;
	int		map_width;
	char	**map;

	map_start = ft_find_map_start(lst);
	if (!map_start)
		return (NULL);
	map_height = ft_find_map_height(map_start);
	map_width = ft_find_map_width(map_start);
	map = ft_malloc_map(map_start, map_height, map_width);
	ft_lstclear(&map_start, free);
	return (map);
}
