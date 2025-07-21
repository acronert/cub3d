/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:07:44 by alex              #+#    #+#             */
/*   Updated: 2024/02/26 18:41:56 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_normalize_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	else if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	else if (angle == 0)
		angle = 2 * M_PI;
	return (angle);
}

void	ft_pixtobuf(char *buf, int red, int green, int blue)
{
	buf[0] = (unsigned char)blue;
	buf[1] = (unsigned char)green;
	buf[2] = (unsigned char)red;
}

void	ft_pixel_dup(char *buf, char *texture)
{
	buf[0] = texture[0];
	buf[1] = texture[1];
	buf[2] = texture[2];
}

void	ft_normalize_target(t_coord *target, t_texture *texture)
{
	if (target->y < 0)
		target->y = 0;
	else if (target->y > texture->size.x)
		target->y = 0;
	if (target->x < 0)
		target->x = 0;
	else if (target->x > texture->size.x)
		target->x = 0;
}
