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
		ft_putpixel(x, roof, game->col[COL_C], game);
	while (floor-- > end_point)
		ft_putpixel(x, floor, game->col[COL_F], game);
}

static void	draw_column(int height, int x, t_cubed *game)
{
	int32_t	color;
	int		endpoint;
	int		startpoint;
	int		repeatpixel;
	int		i;

	endpoint = SCREEN_HEIGHT / 2 + height / 2;
	startpoint = SCREEN_HEIGHT / 2 - height / 2;
	if (startpoint < MAPCELL * MAPGRID
		&& x < MAPCELL * MAPGRID)
		startpoint = MAPCELL * MAPGRID;
	draw_space(startpoint, endpoint, x, game);
	repeatpixel = height / CELLSIZE;
	while (startpoint < endpoint)
	{
		i = 0;
		color = 255; // get texture color instead
		while (i < repeatpixel && startpoint < endpoint)
		{
			ft_putpixel(x, startpoint, color, game);
			startpoint++;
			i++;
		}
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
	int			column;

	column = 0;
	angle = game->cam->a;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (column < SCREEN_WIDTH)
	{
		ray.a = angle;
		calculate_ray(&ray, game);
		fix_fisheye(&ray, game);
		height = CELLSIZE * SCREEN_HEIGHT / ray.d;
		if (height > SCREEN_HEIGHT)
			height = SCREEN_HEIGHT;
		draw_column(height, column, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		column++;
	}
}
