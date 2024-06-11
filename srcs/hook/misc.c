/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:21:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 14:20:04 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	hook_close(void *param)
{
	t_cubed	*game;

	game = param;
	free_exit(game, NOERROR);
}

void	set_buffer(int *buffer, int size, t_cubed *game)
{
	buffer[X] = size;
	buffer[Y] = size;
	if (game->cam->dx < 0)
		buffer[X] = -buffer[X];
	if (game->cam->dy < 0)
		buffer[Y] = -buffer[Y];
}

void	get_map_position(int *target, int x, int y)
{
	target[X] = x / CELLSIZE;
	target[Y] = y / CELLSIZE;
}

char	get_map_element(int x, int y, t_cubed *game)
{
	char	c;

	safe_mutex(&game->mtx[MTX_MAP], MTX_LOCK, game);
	c = game->map->matrix[y][x];
	safe_mutex(&game->mtx[MTX_MAP], MTX_UNLOCK, game);
	return (c);
}
