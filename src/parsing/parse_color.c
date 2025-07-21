/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <mshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:55:57 by acronert          #+#    #+#             */
/*   Updated: 2024/02/28 15:10:00 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_color_value(char *str, unsigned char *color)
{
	int	i;

	if (ft_strlen(str) > 3 || ft_strlen(str) == 0)
		return (FAILURE);
	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (FAILURE);
	}
	i = ft_atoi(str);
	if (i < 0 || i > 255)
		return (FAILURE);
	*color = i;
	return (SUCCESS);
}

int	ft_init_color(t_color *color, char *str)
{
	char	**arr;

	if (color->set)
		return (FAILURE);
	color->set = 1;
	color->red = 0;
	color->green = 0;
	color->blue = 0;
	arr = ft_split(str, ',');
	if (!arr)
		return (FAILURE);
	if (ft_arrlen(arr) != 3)
		return (ft_free_double_char(arr), FAILURE);
	if (ft_get_color_value(arr[0], &color->red) == FAILURE
		|| ft_get_color_value(arr[1], &color->green) == FAILURE
		|| ft_get_color_value(arr[2], &color->blue) == FAILURE)
		return (ft_free_double_char(arr), FAILURE);
	ft_free_double_char(arr);
	return (SUCCESS);
}
