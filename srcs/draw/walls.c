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

/* static void	draw_floor(int x, int height, t_vector *ray, t_cubed *game) */
/* { */
/* 	float	deg; */
/* 	float	fix; */
/* 	int		y; */
/**/
/* 	y = SCREEN_HEIGHT + 1; */
/* 	deg = ft_degtorad(ray->a); */
/* 	while (y-- > height) */
/* 	{ */
/* 		ft_putpixel(x, y, game->color[COL_F], game); */
/* 	} */
/* } */

static void	draw_space(int start_point, int end_point, int x, t_cubed *game)
{
	int	floor;
	int	roof;

	roof = -1;
	floor = SCREEN_HEIGHT + 1;
	while (roof++ < start_point)
	{
		if (roof < MAPCELL * MAPGRID && x < MAPCELL * MAPGRID)
			continue ;
		ft_putpixel(x, roof, game->color[COL_C], game);
	}
	while (floor-- > end_point)
		ft_putpixel(x, floor, game->color[COL_F], game);
}

static void	draw_column(int height, int x, t_vector *ray, t_cubed *game)
{
	int		point[2];
	int32_t	color;

	point[A] = SCREEN_HEIGHT / 2 - height / 2 - 1;
	point[B] = SCREEN_HEIGHT / 2 + height / 2;
	draw_space(point[A], point[B], x, game);
	/* draw_floor(x, point[Y_END], ray, game); */
	while (point[A]++ < point[B])
	{
		color = get_color(game->image[ray->img], ray->x, ray->y);
		ray->y += ray->d;
		if (point[A] < MAPCELL * MAPGRID && x < MAPCELL * MAPGRID)
			continue ;
		ft_putpixel(x, point[A], color, game);
	}
}

static void	calculate_draw(int *height, t_vector *ray)
{
	if (ray->img == IMG_NO)
	{
		ray->x = (int)(ray->y) % CELLSIZE;
		if (ray->a > NORTH && ray->a < SOUTH)
			ray->img = IMG_SO;
	}
	else
	{
		ray->x = (int)(ray->x) % CELLSIZE;
		if (ray->a > WEST)
			ray->img = IMG_EA;
	}
	ray->y = 0;
	ray->d = (float)CELLSIZE / *height;
	if (*height > SCREEN_HEIGHT)
	{
		ray->y = (*height - SCREEN_HEIGHT) / 2 * ray->d;
		*height = SCREEN_HEIGHT;
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
		calculate_draw(&height, &ray);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		draw_column(height, column, &ray, game);
		column++;
	}
}
