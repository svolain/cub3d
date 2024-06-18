/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:39:10 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/18 14:04:31 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

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
		game->animation->active = 1;
	game->mouse[X] = mouse[X];
}
/*
void	hook_click(void *param)
{
	t_cubed	*game;

	game = param;
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		game->animation->active = 1;
}*/

void	hook_animation(void *param)
{
	t_cubed	*game;

	game = (t_cubed *) param;
	animate_shotgun(game);
}
