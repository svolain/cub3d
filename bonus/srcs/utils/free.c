/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/17 15:22:56 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	destruct_map(t_mapinfo *map)
{
	if (map->matrix != NULL)
		free_double(&map->matrix);
	free(map);
	map = NULL;
}

static void	clean_images(t_cubed *game)
{
	int	i;

	i = 0;
	while (i < GAME_ASSETS)
	{
		if (game->asset[i] != NULL)
			mlx_delete_image(game->mlx, game->asset[i]);
		i++;
	}
	i = 0;
	while (i < GAME_ANIMS)
	{
		if (game->anim[i] != NULL)
			mlx_delete_image(game->mlx, game->asset[i]);
		i++;
	}
}

static void	join_threads(t_cubed *game)
{
	int	i;

	i = 0;
	set_game_over(game);
	while (i < GAME_THREADS)
	{
		safe_thread(&game->tid[i], THD_JOIN, game);
		i++;
	}
	i = 0;
	while (i < GAME_MUTEXES)
	{
		safe_mutex(&game->mtx[i], MTX_DESTROY, game);
		i++;
	}
}

void	free_exit(t_cubed *game, int excode)
{
	if (!game)
		exit(excode);
	join_threads(game);
	if (game->mlx != NULL)
	{
		mlx_close_window(game->mlx);
		clean_images(game);
		mlx_terminate(game->mlx);
	}
	if (game->map != NULL)
		destruct_map(game->map);
	if (game->cam != NULL)
		free(game->cam);
	if (game->wpn != NULL)
		free(game->wpn);
	if (game->gnl != NULL)
		free_single(&game->gnl);
	exit(excode);
}
