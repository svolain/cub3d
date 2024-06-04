/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:30:49 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/03 16:03:34 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	animate_minimap(t_cubed *game)
{
	static int	i;
	mlx_image_t	*old;
	mlx_image_t	*new;

	old = game->image[IMG_PS];
	i++;
	if (i > 2)
		i = 0;
	new = game->image[i];
	ft_memcpy(old->pixels, new->pixels,
			old->height * old->width * sizeof(int32_t));
}

static void	check_collision(float *dest, t_action action, t_cubed *game)
{
	int xo = BUMP_BUFFER;
	if (game->cam->dx < 0)
		xo = -xo;
	int yo = BUMP_BUFFER;
	if (game->cam->dy < 0)
		yo = -yo;
	int px = game->cam->x / CELLSIZE;
	int py = game->cam->y / CELLSIZE;
	int xa = (xo + game->cam->x) / CELLSIZE;
	int ya = (yo + game->cam->y) / CELLSIZE;
	int xs = (game->cam->x - xo) / CELLSIZE;
	int ys = (game->cam->y - yo) / CELLSIZE;

	if (action == MOVE_UP)
	{
		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[py][xa]))
			game->cam->x = dest[X];
		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ya][px]))
			game->cam->y = dest[Y];
	}
	else if (action == MOVE_DOWN)
	{
		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[py][xs]))
			game->cam->x = dest[X];
		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ys][px]))
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
	check_collision(destination, action, game);
	animate_minimap(game);
}
