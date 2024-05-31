/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:46:36 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/31 15:34:57 by jmertane         ###   ########.fr       */
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
	game->mouse[X] = mouse[X];
	if (mouse[X] > game->mlx->width || mouse[X] < 0)
		mlx_set_mouse_pos(game->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
