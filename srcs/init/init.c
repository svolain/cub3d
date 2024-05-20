/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/18 13:05:52 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

char *test_map[] = { "11111111\n",
				"10100001\n",
				"10100001\n",
				"10100001\n",
				"10000001\n",
				"10000101\n",
				"10000001\n",
				"11111111" };

static void	init_hooks(t_cubed *game)
{
	mlx_close_hook(game->mlx, &close_window, game);
	mlx_key_hook(game->mlx, &keyhooks, game);
}

static void	init_map(t_mapinfo *map, t_camera *cam, char *file)
{
	int	i;

	i = 0;
	map->fd = -1;
	map->file = file;
	map->matrix = test_map;
	map->width = 8;
	map->height = 8;
	cam->x = 4 * CELLSIZE;
	cam->y = 4 * CELLSIZE;
	cam->a = NORTH - 0.0001f;
}

void	init_game(t_cubed *game, char *file)
{
	ft_bzero(game, sizeof(t_cubed));
	game->map = safe_calloc(sizeof(t_mapinfo), game);
	game->cam = safe_calloc(sizeof(t_camera), game);
	init_map(game->map, game->cam, file);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE, false);
	
	//start drawing minimap
	if (!game->mlx)
		error_exit(ERR_MLX, MSG_MLX, game);
	init_minimap(game);
	init_hooks(game);
}
