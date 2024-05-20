/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:30:49 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/20 16:04:07 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	rotate_camera(t_cubed *game, t_action action)
{
	if (action == ROTATE_LEFT)
	{
		game->cam->a -= STEP_ANGLE;
		check_rotation(&game->cam->a, ROTATE_LEFT);
	}
	else if (action == ROTATE_RIGHT)
	{
		game->cam->a += STEP_ANGLE;
		check_rotation(&game->cam->a, ROTATE_RIGHT);
	}
	calculate_rays(game);
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
	calculate_rays(game);
	move_minimap(game, action);
}

void	keyhooks(mlx_key_data_t keydata, void *param)
{
	t_cubed		*game;
	
	game = param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			close_window(game);
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
