/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/16 16:08:35 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	escape_window(mlx_key_data_t keydata, void *param)
{
	t_cubed	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE
		&& keydata.action == MLX_PRESS)
	{
		free_exit(game);
		exit (NOERROR);
	}
}

void	close_window(void *param)
{
	t_cubed	*game;

	game = param;
	free_exit(game);
	exit (NOERROR);
}

static void	clean_assets(t_texture **lst, t_cubed *game)
{
	t_texture	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->fd != -1)
			close((*lst)->fd);
		if ((*lst)->img != NULL)
			mlx_delete_image(game->mlx, (*lst)->img);
		if ((*lst)->tex != NULL)
			mlx_delete_texture((*lst)->tex);
		if ((*lst)->vec != NULL)
			free((*lst)->vec);
		free(*lst);
		*lst = temp;
	}
	free(*lst);
	*lst = NULL;
}

static void	destruct_map(t_mapinfo *map, t_cubed *game)
{
	int	i;

	if (map->fd != -1)
		close(map->fd);
	if (map->tex != NULL)
		clean_assets(&map->tex, game);
	if (map->matrix != NULL)
	{
		i = 0;
		while (*map->matrix[i])
			free(map->matrix[i++]);
		free(map->matrix);
		map->matrix = NULL;
	}
	free(map);
	map = NULL;
}

void	free_exit(t_cubed *game)
{
	if (!game)
		return ;
	if (game->mlx != NULL)
		mlx_close_window(game->mlx);
	if (game->map != NULL)
		destruct_map(game->map, game);
	if (game->tex != NULL)
		clean_assets(&game->tex, game);
	if (game->mlx != NULL)
		mlx_terminate(game->mlx);
	if (game->cam != NULL)
		free(game->cam);
}
