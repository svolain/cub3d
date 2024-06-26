/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:39:35 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/26 11:31:43 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

/* void	a(t_camera *cam, float angle, t_cubed *game) */
/* { */
/* 	int	x; */
/* 	int	y; */
/**/
/* 	x = 0; */
/* 	while (x < game->map->width) */
/* 	{ */
/* 		y = 0; */
/* 		while (y < game->map->height) */
/* 		{ */
/* 			y++; */
/* 		} */
/* 		x++; */
/* 	} */
/* } */

void	draw_sprites(t_camera *cam, float angle, t_cubed *game)
{
	int	size = 512;

	float spx = (game->map->width - 4) * CELLSIZE - CELLSIZE / 2;
	float spy = 2 * CELLSIZE;
	float spz = SCREEN_HEIGHT / 2;

	float sx = spx - cam->x;
	float sy = spy - cam->y;
	float sz = spz;

	float tmpx = sy * -cos(angle) + sx * sin(angle);
	float tmpy = sx * cos(angle) + sy * sin(angle);

	sx = tmpx;
	sy = tmpy;

	sx = (sx * -2000 / sy) + (SCREEN_WIDTH / 2);
	sy = (sz * 400 / sy) + (SCREEN_HEIGHT / 2);

	float scale = size / tmpy * 2000.0f;
	int x;
	int y;

	float tx = 0;
	float ty = size;
	float dtx = size / scale;
	float dty = size / scale;

	int32_t	color;
	x = sx - scale / 2;
	while (x < sx + scale / 2)
	{
		y = 0;
		ty = size;
		while (y < scale)
		{
			color = get_pixel_color(game->asset[IMG_AM], tx, ty);
			if (ft_valid_pixel(game->asset[IMG_OL], x, sy - y))
				mlx_put_pixel(game->asset[IMG_OL], x, sy - y, color);
			ty -= dty;
			y++;
		}
		tx += dtx;
		x++;
	}
}
