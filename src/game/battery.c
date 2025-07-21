/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battery.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:53:13 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 13:53:28 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_drain_battery(t_game *game)
{
	struct timeval	current_time;
	int				time;
	float			drain_rate;

	gettimeofday(&current_time, NULL);
	time = current_time.tv_sec;
	drain_rate = 0;
	if (time != game->start_time)
	{
		if (game->mini_map == 1)
			drain_rate = 0.03;
		else if (game->flashlight == 1)
			drain_rate = 0.01;
		game->start_time = time;
		if (game->battery_lvl > 0)
			game->battery_lvl -= drain_rate;
		else
			game->battery_lvl = 0;
	}
}

void	ft_flashlight_flicker(t_game *game)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == FAILURE)
		return ;
	if (current_time.tv_usec % 10 == 0)
	{
		game->flashlight = 1;
	}
	else if (current_time.tv_usec % 7 == 0)
		game->flashlight = 0;
}

void	ft_pick_battery(t_game *game)
{
	t_list		*lst;
	t_list		*previous;
	t_sprite	*sprite;

	lst = game->sprite;
	previous = lst;
	while (lst)
	{
		sprite = ((t_sprite *)lst->content);
		if (sprite->type == TYPE_BATTERY)
		{
			if (sprite->distance <= 0.5)
			{
				game->battery_lvl = 1;
				previous->next = lst->next;
				ft_lstdelone(lst, free);
				lst = previous;
			}
		}
		previous = lst;
		lst = lst->next;
	}
}
