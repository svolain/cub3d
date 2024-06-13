/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 06:14:08 by jmertane         ###   ########.fr       */
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
		if (game->image[i] != NULL)
			mlx_delete_image(game->mlx, game->image[i]);
		i++;
	}
	i = 0;
	while (i < GAME_ANIMS)
	{
		if (game->anim[i] != NULL)
			mlx_delete_image(game->mlx, game->image[i]);
		i++;
	}
}

static void	set_game_over(t_cubed *game)
{
	pthread_t	tid;
	t_mtx		mutex;
	int			i;

	i = 0;
	set_finished(game);
	while (i < GAME_THREADS)
	{
		tid = game->tid[i];
		safe_thread(&tid, THD_JOIN, game);
		i++;
	}
	i = 0;
	while (i < GAME_MUTEXES)
	{
		mutex = game->mtx[i];
		safe_mutex(&mutex, MTX_DESTROY, game);
		i++;
	}
}

void	free_exit(t_cubed *game, int excode)
{
	if (!game)
		exit(excode);
	if (game->mlx != NULL)
	{
		set_game_over(game);
		mlx_close_window(game->mlx);
		clean_images(game);
		mlx_terminate(game->mlx);
	}
	if (game->map != NULL)
		destruct_map(game->map);
	if (game->cam != NULL)
		free(game->cam);
	if (game->gnl != NULL)
		free_single(&game->gnl);
	exit(excode);
}
