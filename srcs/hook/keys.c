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
	draw_walls(game);
	move_minimap(game, action);
}

static void	move_camera(t_cubed *game, t_action action)
{
	if (action == MOVE_UP)
		game->cam->y -= STEP_MOVEMENT;
	else if (action == MOVE_DOWN)
		game->cam->y += STEP_MOVEMENT;
	else if (action == MOVE_LEFT)
		game->cam->x -= STEP_MOVEMENT;
	else if (action == MOVE_RIGHT)
		game->cam->x += STEP_MOVEMENT;
	draw_walls(game);
	move_minimap(game, action);
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
