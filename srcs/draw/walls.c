/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:35:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/03 09:11:27 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

/* static void	draw_floor(int x, int y, t_vector *ray, t_cubed *game) */
/* { */
/* 	int32_t	color; */
/* 	float	offset; */
/* 	float	ty; */
/* 	float	tx; */
/**/
/* 	offset = ray->d; */
/* 	ty = CELLSIZE - ray->y; */
/* 	tx = ray->x; */
/* 	while (y < SCREEN_HEIGHT) */
/* 	{ */
/* 		color = get_color(game->image[IMG_FL], ray->x, ty); */
/* 		ft_putpixel(x, y, color, game); */
/* 		ty += offset; */
/* 		tx += offset; */
/* 		y++; */
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

static void	draw_column(int x, int height, t_vector *ray, t_cubed *game)
{
	int		point[2];
	int32_t	color;

	point[A] = SCREEN_HEIGHT / 2 - height / 2 - 1;
	point[B] = SCREEN_HEIGHT / 2 + height / 2;
	/* draw_floor(x, point[B], ray, game); */
	draw_space(point[A], point[B], x, game);
	while (point[A]++ < point[B])
	{
		color = get_color(game->image[ray->img], ray->x, ray->y);
		ray->y += ray->d;
		if (point[A] < MAPCELL * MAPGRID && x < MAPCELL * MAPGRID)
			continue ;
		ft_putpixel(x, point[A], color, game);
	}
}

static void	calculate_draw(int *height, t_vector *ray, t_cubed *game)
{
	int map[2];

	map[X] = ray->x / CELLSIZE;
	map[Y] = ray->y / CELLSIZE;
	if (ray->img == IMG_EA)
		ray->x = (int)(ray->y) % game->image[ray->img]->width;
	else
		ray->x = (int)(ray->x) % game->image[ray->img]->width;
	if (game->map->matrix[map[Y]][map[X]] == 'C')
		ray->img = IMG_FL;
	else if (ray->img == IMG_EA && ray->a > NORTH && ray->a < SOUTH)
		ray->img = IMG_WE;
	else if (ray->img == IMG_SO && ray->a > WEST)
		ray->img = IMG_NO;
	ray->y = 0;
	ray->d = (float)game->image[ray->img]->width / *height;
	if (*height > SCREEN_HEIGHT)
	{
		ray->y = (float)(*height - SCREEN_HEIGHT) / 2 * ray->d;
		*height = SCREEN_HEIGHT;
	}
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
		calculate_draw(&height, &ray, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		draw_column(column, height, &ray, game);
		column++;
	}
}
