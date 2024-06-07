/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:30:49 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/05 14:12:05 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	update_coordinates(float *dest, t_action action, t_cubed *game)
{
	int	buffer[2];
	int	player[2];

	get_position(player, game->cam->x, game->cam->y);
	set_buffer(buffer, BUMP_BUFFER, game);
	int xa = (buffer[X] + game->cam->x) / CELLSIZE;
	int ya = (buffer[Y] + game->cam->y) / CELLSIZE;
	int xs = (game->cam->x - buffer[X]) / CELLSIZE;
	int ys = (game->cam->y - buffer[Y]) / CELLSIZE;

	if (action == MOVE_UP)
	{
		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[player[Y]][xa]))
			game->cam->x = dest[X];
		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ya][player[X]]))
			game->cam->y = dest[Y];
	}
	else if (action == MOVE_DOWN)
	{
		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ys][xa]))
			game->cam->x = dest[X];
		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ya][xs]))
			game->cam->y = dest[Y];
	}
	else if (action == MOVE_LEFT)
	{
		game->cam->x = dest[X];
		game->cam->y = dest[Y];
	}
	else
	{
		game->cam->x = dest[X];
		game->cam->y = dest[Y];
	}
}

void	move_camera(t_cubed *game, t_action action)
{
	float	destination[2];

	if (action == MOVE_UP)
	{
		destination[X] = game->cam->x + game->cam->dx;
		destination[Y] = game->cam->y + game->cam->dy;
	}
	else if (action == MOVE_DOWN)
	{
		destination[X] = game->cam->x - game->cam->dx;
		destination[Y] = game->cam->y - game->cam->dy;
	}
	else if (action == MOVE_LEFT)
	{
		destination[X] = game->cam->x - -game->cam->dy;
		destination[Y] = game->cam->y - game->cam->dx;
	}
	else
	{
		destination[X] = game->cam->x + -game->cam->dy;
		destination[Y] = game->cam->y + game->cam->dx;
	}
	update_coordinates(destination, action, game);
	animate_minimap(game);
}
