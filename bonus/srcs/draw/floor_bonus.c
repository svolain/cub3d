/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:23:09 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 15:40:08 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static int32_t	calculate_shade(int row, int32_t color)
{
	static int	treshold = 450;
	static int	modifier = 140;
	float		intensity;

	if (row <= SCREEN_HEIGHT - treshold)
		return (COLOR_BLACK);
	else
		intensity = (float)row / SCREEN_HEIGHT * 255.0f;
	return (get_alpha_blend(get_rgba(0, 0, 0, modifier - intensity), color));
}

static void	calculate_draw(int row, float *tex, t_camera *cam, t_cubed *game)
{
	float	pp;
	float	dy;
	float	angle;

	angle = cos(fabs(cam->a - cam->dy));
	pp = (float)SCREEN_WIDTH / tan(FOV / 2);
	dy = row - (float)SCREEN_HEIGHT / 2.0f;
	tex[X] = cam->x * 1.4f;
	tex[Y] = -cam->y * 1.4f;
	tex[X] += cos(cam->dy) * pp * 64 / dy / angle;
	tex[Y] -= sin(cam->dy) * pp * 64 / dy / angle;
	tex[X] = (int)tex[X] % game->asset[IMG_FL]->width;
	tex[Y] = (int)tex[Y] % game->asset[IMG_FL]->height;
}

static void	draw_column(int column, int height, t_camera *cam, t_cubed *game)
{
	float	tex[2];
	int32_t	shade;
	int32_t	floor;
	int32_t	roof;
	int		row;

	row = SCREEN_HEIGHT / 2 + height / 2;
	while (row < SCREEN_HEIGHT)
	{
		calculate_draw(row, tex, cam, game);
		shade = calculate_shade(row, game->color[COL_FL]);
		floor = get_alpha_blend(shade, get_pixel_color
				(game->asset[IMG_FL], tex[X], tex[Y]));
		ft_put_pixel(column, row, floor, game->asset[IMG_BG]);
		shade = calculate_shade(row, game->color[COL_RF]);
		roof = get_alpha_blend(shade, get_pixel_color
				(game->asset[IMG_RF], tex[X], tex[Y]));
		ft_put_pixel(column, SCREEN_HEIGHT - row, roof, game->asset[IMG_BG]);
		row++;
	}
}

void	draw_floor(t_camera *cam, float angle, t_cubed *game)
{
	t_vector	ray;
	int			height;
	int			column;

	column = 0;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (column < SCREEN_WIDTH)
	{
		ray.a = angle;
		calculate_ray(&ray, cam, game);
		fix_fisheye(&ray, cam->a);
		cam->dy = ray.a;
		height = CELLSIZE * SCREEN_HEIGHT / ray.d;
		draw_column(column, height, cam, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		column++;
	}
}
