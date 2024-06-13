/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:39:10 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/13 08:39:13 by jmertane         ###   ########.fr       */
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
}
