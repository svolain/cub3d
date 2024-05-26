/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:32:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/14 09:18:53 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

// delete this
char *test_map[] = { "11111111\n",
					"10100001\n",
					"10100001\n",
					"10100001\n",
					"10000001\n",
					"10000101\n",
					"10000001\n",
					"11111111" };

// delete this
static void	init_map(t_cubed *game)
{
	game->map->matrix = test_map;
	game->map->width = 8;
	game->map->height = 8;
	game->cam->x = 4 * CELLSIZE;
	game->cam->y = 4 * CELLSIZE;
	game->cam->a = NORTH - 0.1;
}

static void	launch_hooks(t_cubed *game)
{
	mlx_close_hook(game->mlx, hook_close, game);
	mlx_key_hook(game->mlx, hook_keys, game);
	/* mlx_loop_hook(game->mlx, hook_keys, game->mlx); *///segfaults
	mlx_loop(game->mlx);
}

static void	start_scene(t_cubed *game)
{
	game->img[ELEM_BG] = safe_image(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, game);
	if (mlx_image_to_window(game->mlx, game->img[ELEM_BG], 0, 0) == FAILURE)
		error_exit(ERR_MLX, MSG_MLX, game);
	mlx_image_to_window(game->mlx, game->img[ELEM_NO], 0, 0); // delete this
	/* draw_walls(game); */
	/* init_minimap(game); */
}

static void	parse_infile(t_cubed *game)
{
	parse_filename(game);
	open_infile(game);
	parse_elements(game);
	/* parse_mapinfo(game); */// use this
	init_map(game); // delete this
}

static void	init_game(t_cubed *game, char *file)
{
	ft_bzero(game, sizeof(t_cubed));
	game->cam = safe_calloc(sizeof(t_vector), game);
	game->map = safe_calloc(sizeof(t_mapinfo), game);
	game->map->filename = file;
	game->map->filefd = -1;
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE, false);
	if (!game->mlx)
		error_exit(ERR_MLX, MSG_MLX, game);
}

int	main(int argc, char **argv)
{
	t_cubed	game;

	if (argc != 2)
		error_exit(ERR_ARGC, MSG_ARGC, NULL);
	init_game(&game, argv[1]);
	parse_infile(&game);
	start_scene(&game);
	launch_hooks(&game);
	free_exit(&game, NOERROR);
}
