/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/15 08:18:19 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	free_single(char **str)
{
	free(*str);
	*str = NULL;
}

static void	free_double(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
		free_single(&(*arr)[i++]);
	free(*arr);
	*arr = NULL;
}

static void	destruct_map(t_map *map)
{
	if (map->fd != -1)
		close(map->fd);
	if (map->map != NULL)
		free_double(&map->map);
	free(map);
	map = NULL;
}

static void	clean_assets(t_tex **lst, t_cubed *game)
{
	t_tex	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->fd != -1)
			close((*lst)->fd);
		if ((*lst)->img != NULL)
			mlx_delete_image(game->mlx, (*lst)->img);
		if ((*lst)->tex != NULL)
			mlx_delete_texture((*lst)->tex);
		free(*lst);
		*lst = temp;
	}
	free(*lst);
	*lst = NULL;
}

void	free_exit(t_cubed *game)
{
	if (!game)
		return ;
	if (game->tex != NULL)
		clean_assets(&game->tex, game);
	if (game->mlx != NULL)
		mlx_terminate(game->mlx);
	if (game->map != NULL)
		destruct_map(game->map);
	if (game->cam != NULL)
		free(game->cam);
}
