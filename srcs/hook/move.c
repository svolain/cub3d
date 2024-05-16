/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:09:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/16 16:13:23 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

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
	// TEST: Updating minimap drawing goes here
}

void	move_hook(mlx_key_data_t keydata, void *param)
{
	t_cubed	*game;

	game = param;
	if (keydata.action == MLX_PRESS)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_W))
			move_camera(game, MOVE_UP);
		if (mlx_is_key_down(game->mlx, MLX_KEY_S))
			move_camera(game, MOVE_DOWN);
		if (mlx_is_key_down(game->mlx, MLX_KEY_A))
			move_camera(game, MOVE_LEFT);
		if (mlx_is_key_down(game->mlx, MLX_KEY_D))
			move_camera(game, MOVE_RIGHT);
	}
}