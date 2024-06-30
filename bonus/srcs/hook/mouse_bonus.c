/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:39:10 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/30 11:44:15 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	hook_mouse(void *param)
{
	t_cubed	*game;
	int32_t	mouse[2];

	game = param;
	mlx_get_mouse_pos(game->mlx, &mouse[X], &mouse[Y]);
	if (mouse[X] < game->mouse[X])
		rotate_camera(game, ROTATE_LEFT);
	else if (mouse[X] > game->mouse[X])
		rotate_camera(game, ROTATE_RIGHT);
	else if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		set_status(&game->sprite[SPRT_WPN]->status[SHOOT_WPN],
			true, &game->mtx[MTX_WPN], game);
	game->mouse[X] = mouse[X];
}

void	hook_weapon(void *param)
{
	t_cubed	*game;

	game = (t_cubed *)param;
	weapon_shoot(game->sprite[SPRT_WPN], game);
	weapon_move(game->sprite[SPRT_WPN], game);
	loop_portal(game->sprite[SPRT_GATE], game);
}
