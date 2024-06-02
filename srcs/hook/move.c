/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:30:49 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/31 15:35:03 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

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
		if (game->map->matrix[py][xa] == MAP_FLOOR)
			game->cam->x = dest[X];
		if (game->map->matrix[ya][px] == MAP_FLOOR)
			game->cam->y = dest[Y];
	}
	else if (action == MOVE_DOWN)
	{
		if (game->map->matrix[py][xs] == MAP_FLOOR)
			game->cam->x = dest[X];
		if (game->map->matrix[ys][px] == MAP_FLOOR)
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

static void	move_camera(t_cubed *game, t_action action)
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
}

void	hook_moves(void *param)
{
	t_cubed	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_camera(game, MOVE_UP);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_camera(game, MOVE_DOWN);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_camera(game, MOVE_LEFT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_camera(game, MOVE_RIGHT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_camera(game, ROTATE_RIGHT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_camera(game, ROTATE_LEFT);
}
