/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/30 11:49:11 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static void	destruct_map(t_mapinfo *map)
{
	if (map->matrix != NULL)
		free_double(&map->matrix);
	free(map);
	map = NULL;
}

static void	destruct_plr(t_player *plr, t_cubed *game)
{
	if (plr->ammo != NULL)
		free_single(&plr->ammo);
	if (plr->health != NULL)
		free_single(&plr->health);
	if (plr->img[A] != NULL)
		mlx_delete_image(game->mlx, plr->img[A]);
	if (plr->img[H] != NULL)
		mlx_delete_image(game->mlx, plr->img[H]);
	free(plr);
	plr = NULL;
}

static void	stop_mlx(t_cubed *game)
{
	if (!game->mlx)
		return ;
	mlx_close_window(game->mlx);
	free_assets(game);
	free_sprites(game);
	mlx_terminate(game->mlx);
}

static void	stop_threads(t_cubed *game)
{
	set_game_over(game);
	if (!get_status(&game->status[STAT_LOADED],
			&game->mtx[MTX_LOADED], game))
		return ;
	join_threads(game);
	destroy_mutexes(game);
}

void	free_exit(t_cubed *game, int excode)
{
	if (!game)
		exit(excode);
	stop_threads(game);
	stop_mlx(game);
	if (game->map != NULL)
		destruct_map(game->map);
	if (game->plr != NULL)
		destruct_plr(game->plr, game);
	if (game->cam != NULL)
		free(game->cam);
	if (game->gnl != NULL)
		free_single(&game->gnl);
	exit(excode);
}
