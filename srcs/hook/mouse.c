/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:46:36 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/31 14:46:38 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	rotate_camera(t_cubed *game, t_action action)
{
	if (action == ROTATE_LEFT)
		ft_rotate(&game->cam->a, STEP_ANGLE, ROTATE_LEFT);
	else
		ft_rotate(&game->cam->a, STEP_ANGLE, ROTATE_RIGHT);
	game->cam->dx = cos(game->cam->a) * STEP_MOVEMENT;
	game->cam->dy = sin(game->cam->a) * STEP_MOVEMENT;
}

void	hook_mouse(void *param)
{
	t_cubed	*game;
	int32_t	mouse[2];

	game = param;
	mlx_get_mouse_pos(game->mlx, &mouse[X_COOR], &mouse[Y_COOR]);
	if (mouse[X_COOR] < game->mouse[X_COOR])
		rotate_camera(game, ROTATE_LEFT);
	else if (mouse[X_COOR] > game->mouse[X_COOR])
		rotate_camera(game, ROTATE_RIGHT);
	if (mouse[X_COOR] > game->mlx->width || mouse[X_COOR] < 0)
		mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	game->mouse[X_COOR] = mouse[X_COOR];
}
