/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <mshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:03:19 by acronert          #+#    #+#             */
/*   Updated: 2024/02/28 14:35:13 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_display_list_content(t_list *lst)
{
	t_list	*current;
	int		count;

	current = lst;
	count = 0;
	while (current)
	{
		printf("#%3d : %s\n", count, (char *)current->content);
		current = current->next;
		count++;
	}
}

void	ft_display_double_char(char **arr)
{
	int	y;
	int	x;

	y = 0;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			printf("%c", arr[y][x]);
			x++;
		}
		y++;
		printf("\n");
	}
}

void	ft_remove_lst_space(t_list **lst)
{
	t_list	*previous;
	t_list	*start;

	ft_lstadd_front(lst, ft_lstnew(NULL));
	previous = *lst;
	start = *lst;
	*lst = (*lst)->next;
	while (*lst)
	{
		if (!(char *)(*lst)->content
			|| ft_str_ischarset((char *)(*lst)->content, " "))
		{
			previous->next = (*lst)->next;
			ft_lstdelone(*lst, free);
			*lst = previous->next;
		}
		else
		{
			previous = *lst;
			*lst = (*lst)->next;
		}
	}
	*lst = start->next;
	ft_lstdelone(start, free);
}

t_list	*ft_read_scene_file(int fd)
{
	t_list	*lst;
	char	*line;
	char	*trimmed_line;

	lst = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		trimmed_line = ft_strtrim(line, "\n");
		free(line);
		ft_lstadd_back(&lst, ft_lstnew(trimmed_line));
	}
	return (lst);
}

int	ft_parsing(t_game *game, char *filename, int fd)
{
	t_list	*lst;

	if (ft_strncmp(ft_strchr(filename, '.'), ".cub", 5))
		return (printf("Error : not a .cub file\n"), FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error : not a valid scene file\n"), FAILURE);
	lst = ft_read_scene_file(fd);
	close (fd);
	if (!lst)
		return (printf("Error : empty file\n"), FAILURE);
	game->map = ft_create_map(lst);
	if (ft_check_map_validity(game) == FAILURE)
	{
		ft_lstclear(&lst, free);
		return (printf("Error : invalid map\n"), FAILURE);
	}
	ft_remove_lst_space(&lst);
	game->display = ft_parse_texture(&lst);
	if (!game->display)
	{
		ft_lstclear(&lst, free);
		return (printf("Error : invalid textures\n"), FAILURE);
	}
	return (SUCCESS);
}
