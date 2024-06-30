/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:11:43 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 14:01:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	get_map_position(int target[2], int x, int y)
{
	target[X] = x / CELLSIZE;
	target[Y] = y / CELLSIZE;
}

void	set_map_element(int x, int y, char c, t_cubed *game)
{
	safe_mutex(&game->mtx[MTX_MAP], MTX_LOCK, game);
	game->map->matrix[y][x] = c;
	safe_mutex(&game->mtx[MTX_MAP], MTX_UNLOCK, game);
}

char	get_map_element(int x, int y, t_cubed *game)
{
	char	c;

	safe_mutex(&game->mtx[MTX_MAP], MTX_LOCK, game);
	c = game->map->matrix[y][x];
	safe_mutex(&game->mtx[MTX_MAP], MTX_UNLOCK, game);
	return (c);
}
