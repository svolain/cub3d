/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:56:17 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/30 11:52:40 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	draw_screen_fx(int32_t color, t_cubed *game)
{
	int		screen[2];

	screen[X] = 0;
	safe_mutex(&game->mtx[MTX_FX], MTX_LOCK, game);
	while (screen[X] < SCREEN_WIDTH)
	{
		screen[Y] = 0;
		while (screen[Y] < SCREEN_HEIGHT)
		{
			ft_put_pixel(screen[X], screen[Y], color, game->asset[IMG_FX]);
			screen[Y]++;
		}
		screen[X]++;
	}
	game->asset[IMG_FX]->enabled = true;
	wait_frame(game, 10000);
	game->asset[IMG_FX]->enabled = false;
	safe_mutex(&game->mtx[MTX_FX], MTX_UNLOCK, game);
}

void	draw_hud(t_cubed *game)
{
	int	height;
	int	width;

	height = SCREEN_HEIGHT - HUD_HEIGHT;
	while (height == SCREEN_HEIGHT)
	{
		width = 0;
		while (width < SCREEN_WIDTH)
		{
			ft_put_pixel(width, height, COLOR_HUD, game->asset[IMG_HD]);
			width++;
		}
		height++;
	}
}
