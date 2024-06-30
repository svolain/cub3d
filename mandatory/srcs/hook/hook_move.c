/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 06:47:11 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/18 18:45:42 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	hook_close(void *param)
{
	t_cubed	*game;

	game = param;
	free_exit(game, NOERROR);
}

void	hook_action(mlx_key_data_t keydata, void *param)
{
	t_cubed		*game;

	game = param;
	if (keydata.action == MLX_PRESS)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
			free_exit(game, NOERROR);
	}
}

void	move_camera(t_cubed *game, t_action action)
{
	if (action == MOVE_UP)
	{
		game->cam->x += game->cam->dx;
		game->cam->y += game->cam->dy;
	}
	else if (action == MOVE_DOWN)
	{
		game->cam->x -= game->cam->dx;
		game->cam->y -= game->cam->dy;
	}
	else if (action == MOVE_LEFT)
	{
		game->cam->x -= -game->cam->dy;
		game->cam->y -= game->cam->dx;
	}
	else
	{
		game->cam->x += -game->cam->dy;
		game->cam->y += game->cam->dx;
	}
}

void	hook_movement(void *param)
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
