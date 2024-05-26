/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:35:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/18 22:04:22 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	draw_space(int start_point, int end_point, int x, t_cubed *game)
{
	int	floor;
	int	roof;

	roof = -1;
	floor = SCREEN_HEIGHT + 1;
	while (roof++ < start_point)
	{
		mlx_put_pixel(game->img[ELEM_BG], x, roof, game->col[COL_C]);
	}
	while (floor-- > end_point)
	{
		mlx_put_pixel(game->img[ELEM_BG], x, floor, game->col[COL_F]);
	}
}

static void	draw_segment(int height, int x, t_cubed *game)
{
	int	start_point;
	int	end_point;

	start_point = SCREEN_HEIGHT / 2 - height / 2 - 1;
	end_point = SCREEN_HEIGHT / 2 + height / 2;
	draw_space(start_point, end_point, x, game);
	while (start_point++ < end_point)
	{
		if (x < MAPCELL * MAPGRID
			&& start_point < MAPCELL * MAPGRID)
			continue ;
		mlx_put_pixel(game->img[ELEM_BG], x, start_point, 255);
	}
}

static void	fix_fisheye(t_vector *ray, t_cubed *game)
{
	float	angle;

	angle = game->cam->a;
	ft_rotate(&angle, ray->a, ROTATE_LEFT);
	ray->d *= cos(angle);
}

void	draw_walls(t_cubed *game)
{
	t_vector	ray;
	float		angle;
	int			height;
	int			x;

	x = 0;
	angle = game->cam->a;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (x < SCREEN_WIDTH)
	{
		ray.a = angle;
		calculate_ray(&ray, game);
		fix_fisheye(&ray, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		height = CELLSIZE * SCREEN_HEIGHT / ray.d;
		if (height > SCREEN_HEIGHT)
			height = SCREEN_HEIGHT;
		draw_segment(height, x, game);
		x++;
	}
}
