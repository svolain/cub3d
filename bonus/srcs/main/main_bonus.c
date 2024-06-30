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

#include <cubed_bonus.h>

static void	run_game(t_cubed *game)
{
	mlx_close_hook(game->mlx, hook_close, game);
	mlx_key_hook(game->mlx, hook_action, game);
	mlx_loop_hook(game->mlx, hook_movement, game);
	mlx_loop_hook(game->mlx, hook_mouse, game);
	mlx_loop_hook(game->mlx, hook_weapon, game);
	init_player_info(game);
	mlx_loop(game->mlx);
}

static void	load_scene(t_cubed *game)
{
	safe_draw(game->asset[IMG_BG], 0, 0, game);
	safe_draw(game->asset[IMG_FG], 0, 0, game);
	safe_draw(game->asset[IMG_OL], 0, 0, game);
	safe_draw(game->asset[IMG_MM], 0, 0, game);
	safe_draw(game->asset[IMG_FV], 0, 0, game);
	draw_weapon_frames(game->sprite[SPRT_WPN], game);
	safe_draw(game->asset[IMG_PL], MAPCENTER, MAPCENTER, game);
	safe_draw(game->asset[IMG_HD], 0, SCREEN_HEIGHT - HUD_HEIGHT, game);
	safe_draw(game->asset[IMG_FX], 0, 0, game);
	safe_mutex(0, MTX_INIT, game);
	safe_thread(0, THD_CREATE, game);
	set_status(&game->status[STAT_LOADED],
		true, &game->mtx[MTX_LOADED], game);
}

static void	parse_file(t_cubed *game)
{
	parse_filename(game);
	open_infile(game);
	parse_elements(game);
	parse_mapinfo(game);
}

static void	init_game(t_cubed *game, char *file)
{
	ft_bzero(game, sizeof(t_cubed));
	game->cam = safe_calloc(sizeof(t_camera), game);
	game->plr = safe_calloc(sizeof(t_player), game);
	game->map = safe_calloc(sizeof(t_mapinfo), game);
	game->map->filename = file;
	game->map->filefd = -1;
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE, false);
	if (!game->mlx)
		error_exit(ERR_MLX, MSG_MLX, game);
	mlx_get_mouse_pos(game->mlx, &game->mouse[X], &game->mouse[Y]);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	init_sprite(SPRT_WPN, FRAMES_WEAPON, FRAME_DELAY, game);
	init_sprite(SPRT_GATE, FRAMES_PORTAL, FRAME_DELAY, game);
	load_weapon_frames(game->sprite[SPRT_WPN], game);
	load_portal_frames(game->sprite[SPRT_GATE], game);
	load_custom_assets(game);
}

int	main(int argc, char **argv)
{
	t_cubed	game;

	if (argc != 2)
		error_exit(ERR_ARGC, MSG_ARGC, NULL);
	init_game(&game, argv[1]);
	parse_file(&game);
	load_scene(&game);
	run_game(&game);
	free_exit(&game, NOERROR);
}
