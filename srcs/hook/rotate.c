/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:09:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/16 16:13:03 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	rotate_camera(t_cubed *game, t_action action)
{
	if (action == ROTATE_LEFT)
	{
		game->cam->a -= STEP_ANGLE;
		if (game->cam->a < 0)
			game->cam->a += 2 * PI;
	}
	else if (action == ROTATE_RIGHT)
	{
		game->cam->a += STEP_ANGLE;
		if (game->cam->a > 2 * PI)
			game->cam->a -= 2 * PI;
	}
	calculate_rays(game);
	// TEST: Updating minimap drawing goes here
}

void	rotate_hook(mlx_key_data_t keydata, void *param)
{
	t_cubed	*game;

	game = param;
	if (keydata.action == MLX_PRESS)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_camera(game, ROTATE_RIGHT);
		if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
			rotate_camera(game, ROTATE_LEFT);
	}
	// TODO: add mouse hooks to calculate where cursor is moving
	// and rotate player based on calculations (BONUS)
}