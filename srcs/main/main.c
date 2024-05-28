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

static void	run_game(t_cubed *game)
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
	draw_walls(game);
	init_minimap(game);
}

static void	parse_infile(t_cubed *game)
{
	parse_filename(game);
	open_infile(game);
	parse_elements(game);
	parse_mapinfo(game);
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
	run_game(&game);
	free_exit(&game, NOERROR);
}
