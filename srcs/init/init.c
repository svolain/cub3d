/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/22 12:20:02 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>
/*
char *test_map[] = { "11111111\n",
					"10100001\n",
					"10100001\n",
					"10100001\n",
					"10000001\n",
					"10000101\n",
					"10000001\n",
					"11111111" };*/

static void	init_map(t_mapinfo *map, t_camera *cam, char *file)
{
	map->fd = -1;
	map->file = file;
	map->matrix = NULL;
	map->width = 0;
	map->height = 0;
	map->tex = NULL;
	cam->x = 4 * CELLSIZE;
	cam->y = 4 * CELLSIZE;
	cam->a = NORTH - 0.1;
}

void	init_game(t_cubed *game, char *file)
{
	ft_bzero(game, sizeof(t_cubed));
	game->map = safe_calloc(sizeof(t_mapinfo), game);
	game->cam = safe_calloc(sizeof(t_camera), game);
	init_map(game->map, game->cam, file);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE, false);
	if (!game->mlx)
		error_exit(ERR_MLX, MSG_MLX, game);
	parse_map(game);
	init_minimap(game);
}
