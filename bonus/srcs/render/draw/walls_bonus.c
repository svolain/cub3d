/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:35:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/28 13:56:41 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static void	transparent_void(int column, int height, t_cubed *game)
{
	while (height < SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->asset[IMG_FG],
			column, height, TRANSPARENT);
		mlx_put_pixel(game->asset[IMG_FG],
			column, SCREEN_HEIGHT - height, TRANSPARENT);
		height++;
	}
}

static int32_t	calculate_shade(int height, t_vector *ray)
{
	static int	treshold = 210;
	float		intensity;

	if (height <= treshold)
		return (COLOR_BLACK);
	else
		intensity = (float)height / SCREEN_HEIGHT * 255.0f;
	return (get_rgba(0, 0, 0, ray->a - intensity));
}

static void	draw_column(int column, int height, t_vector *ray, t_cubed *game)
{
	int		point[2];
	int32_t	shade;
	int32_t	color;

	point[A] = SCREEN_HEIGHT / 2 - height / 2;
	point[B] = SCREEN_HEIGHT / 2 + height / 2;
	transparent_void(column, point[B], game);
	shade = calculate_shade(height, ray);
	while (point[A] < point[B])
	{
		color = get_alpha_blend(shade, get_pixel_color
				(game->asset[ray->img], ray->x, ray->y));
		ft_put_pixel(column, point[A], color, game->asset[IMG_FG]);
		ray->y += ray->d;
		point[A]++;
	}
}

void	draw_walls(t_camera *cam, float angle, t_cubed *game)
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
		height = CELLSIZE * SCREEN_HEIGHT / ray.d;
		calculate_wall(&height, &ray, game);
		draw_column(column, height, &ray, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		column++;
	}
}
