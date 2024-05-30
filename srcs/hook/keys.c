/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:30:49 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/25 14:35:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	rotate_camera(t_cubed *game, t_action action)
{
	if (action == ROTATE_LEFT)
		ft_rotate(&game->cam->a, STEP_ANGLE, ROTATE_LEFT);
	else if (action == ROTATE_RIGHT)
		ft_rotate(&game->cam->a, STEP_ANGLE, ROTATE_RIGHT);
	game->cam->dx = cos(game->cam->a) * STEP_MOVEMENT;
	game->cam->dy = sin(game->cam->a) * STEP_MOVEMENT;
	draw_walls(game);
	draw_minimap(game);
}

static void	update_coordinates(float *dest, t_action action, t_cubed *game)
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
		if (game->map->matrix[py][xa] != MAP_WALL)
			game->cam->x = dest[X_COOR];
		if (game->map->matrix[ya][px] != MAP_WALL)
			game->cam->y = dest[Y_COOR];
	}
	else if (action == MOVE_DOWN)
	{
		if (game->map->matrix[py][xs] != MAP_WALL)
			game->cam->x = dest[X_COOR];
		if (game->map->matrix[ys][px] != MAP_WALL)
			game->cam->y = dest[Y_COOR];
	}
	else if (action == MOVE_LEFT)
	{
		game->cam->x = dest[X_COOR];
		game->cam->y = dest[Y_COOR];
	}
	else
	{
		game->cam->x = dest[X_COOR];
		game->cam->y = dest[Y_COOR];
	}
	/* if (action == MOVE_LEFT) */
	/* { */
	/* 	if (game->map->matrix[ya][xs] != MAP_WALL */
	/* 		&& game->map->matrix[ys][xs] != MAP_WALL) */
	/* 		game->cam->x = dest_x; */
	/* 	if (game->map->matrix[ys][xa] != MAP_WALL */
	/* 		&& game->map->matrix[ys][xs] != MAP_WALL) */
	/* 		game->cam->y = dest_y; */
	/* } */
}

static void	move_camera(t_cubed *game, t_action action)
{
	float	dest[2];

	if (action == MOVE_UP)
	{
		dest[X_COOR] = game->cam->x + game->cam->dx;
		dest[Y_COOR] = game->cam->y + game->cam->dy;
	}
	else if (action == MOVE_DOWN)
	{
		dest[X_COOR] = game->cam->x - game->cam->dx;
		dest[Y_COOR] = game->cam->y - game->cam->dy;
	}
	else if (action == MOVE_LEFT)
	{
		dest[X_COOR] = game->cam->x - -game->cam->dy;
		dest[Y_COOR] = game->cam->y - game->cam->dx;
	}
	else
	{
		dest[X_COOR] = game->cam->x + -game->cam->dy;
		dest[Y_COOR] = game->cam->y + game->cam->dx;
	}
	update_coordinates(dest, action, game);
	draw_walls(game);
	draw_minimap(game);
}

void	hook_keys(mlx_key_data_t keydata, void *param)
{
	t_cubed		*game;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
			free_exit(game, NOERROR);
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
}

/* void	hook_keys(void *param) */
/* { */
/* 	t_cubed	*game; */
/**/
/* 	game = param; */
/* 	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) */
/* 		hook_close(game); */
/* 	if (mlx_is_key_down(game->mlx, MLX_KEY_W)) */
/* 		move_camera(game, MOVE_UP); */
/* 	if (mlx_is_key_down(game->mlx, MLX_KEY_S)) */
/* 		move_camera(game, MOVE_DOWN); */
/* 	if (mlx_is_key_down(game->mlx, MLX_KEY_A)) */
/* 		move_camera(game, MOVE_LEFT); */
/* 	if (mlx_is_key_down(game->mlx, MLX_KEY_D)) */
/* 		move_camera(game, MOVE_RIGHT); */
/* 	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)) */
/* 		rotate_camera(game, ROTATE_RIGHT); */
/* 	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)) */
/* 		rotate_camera(game, ROTATE_LEFT); */
/* } */
