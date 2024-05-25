/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/25 19:51:24 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	free_single(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

/* static void	free_double(char ***arr) */
/* { */
/* 	int	i; */
/**/
/* 	if (!arr || !*arr) */
/* 		return ; */
/* 	i = 0; */
/* 	while ((*arr)[i]) */
/* 		free_single(&(*arr)[i++]); */
/* 	free(*arr); */
/* 	*arr = NULL; */
/* } */

static void	destruct_map(t_mapinfo *map)
{
	/* if (map->matrix != NULL) */
	/* 	free_double(&map->matrix); */
	free(map);
	map = NULL;
}

static void	clean_assets(t_cubed *game)
{
	mlx_image_t	*image;
	int			i;

	i = 0;
	while (i < GAME_ASSETS)
	{
		image = game->img + i;
		if (image != NULL)
			mlx_delete_image(game->mlx, image);
		i++;
	}
}

void	free_exit(t_cubed *game, int excode)
{
	if (!game)
		exit(excode);
	if (game->mlx != NULL)
		mlx_close_window(game->mlx);
	if (game->map != NULL)
		destruct_map(game->map);
	if (game->img != NULL)
		clean_assets(game);
	if (game->mlx != NULL)
		mlx_terminate(game->mlx);
	if (game->cam != NULL)
		free(game->cam);
	if (game->gnl != NULL)
		free_single(&game->gnl);
	exit(excode);
}
