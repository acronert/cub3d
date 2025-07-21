/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:51:44 by acronert          #+#    #+#             */
/*   Updated: 2024/02/27 13:25:35 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		printf("./cub3d [MAP].cub\n");
		return (1);
	}
	game = ft_initialization(argv[1]);
	if (!game)
		return (FAILURE);
	ft_input(game);
	ft_exit(game);
}
