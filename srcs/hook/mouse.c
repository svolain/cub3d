/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:46:36 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/05 17:09:28 by vsavolai         ###   ########.fr       */
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
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		animate_shotgun(game);
		ft_memcpy(game->anim[IMG_TO]->pixels, game->anim[IMG_T1]->pixels,
			game->anim[IMG_TO]->height * game->anim[IMG_TO]->width * BPP);
	}
}
