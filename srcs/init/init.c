/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/16 16:18:32 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

char *map[] = { "11111111\n",
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
	mlx_key_hook(game->mlx, &escape_window, game);
	mlx_key_hook(game->mlx, &move_hook, game);
	mlx_key_hook(game->mlx, &rotate_hook, game);
	// TODO: mlx_mouse_hook(game->mlx, &rotate_hook, game);
}

static void	init_map(t_mapinfo *map, t_camera *cam, char *file)
{
	map->fd = -1;
	map->file = file;
	// TODO: map parsing goes here
	map->matrix = map; // gives compiling error...
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
	if (!game->mlx)
		error_exit(ERR_MLX, MSG_MLX, game);
	init_hooks(game);
}
