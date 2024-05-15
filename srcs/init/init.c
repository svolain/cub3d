/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/15 08:17:33 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	init_map(t_map *map, t_cam *cam, char *file)
{
	map->fd = -1;
	map->file = file;
	// TODO: Rest of the function needs map parsing
	// propably need to add t_cubed struct as param
	map->map = {"11111111\n",
				"10100001\n",
				"10100001\n",
				"10100001\n",
				"10000001\n",
				"10000101\n",
				"10000001\n",
				"11111111" };
	map->width = 8;
	map->height = 8;
	cam->x = 4 * CELLSIZE;
	cam->y = 4 * CELLSIZE;
	cam->a = NORTH - DEGREE;
}

void	init_game(t_cubed *game, char *file)
{
	ft_bzero(game, sizeof(t_cubed));
	game->map = safe_calloc(sizeof(t_map), game);
	game->cam = safe_calloc(sizeof(t_cam), game);
	init_map(game->map, game->cam, file);
	game->mlx = mlx_init(
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SCREEN_TITLE,
		false);
}
