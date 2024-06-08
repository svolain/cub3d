/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:35:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/05 20:19:05 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	calculate_draw(int y, float *tex, t_vector *ray, t_cubed *game)
{
	float	pp;
	float	dy;
	float	angle;

	angle = cos(fabs(game->cam->a - ray->a));
	pp = ((float)SCREEN_WIDTH / 2.0f) / tan(FOV / 2.0f);
	dy = y - (float)SCREEN_HEIGHT / 2.0f;
	tex[X] = game->cam->x + cos(ray->a) * pp * CELLSIZE / dy / angle;
	tex[Y] = game->cam->y - sin(ray->a) * pp * CELLSIZE / dy / angle;
	tex[X] = (int)tex[X] % game->image[IMG_FL]->width;
	tex[Y] = (int)tex[Y] % game->image[IMG_FL]->height;
}

static void	draw_background(int x, int y, t_vector *ray, t_cubed *game)
{
	float	tex[2];
	int32_t	floor;
	int32_t	roof;

	while (++y < SCREEN_HEIGHT)
	{
		calculate_draw(y, tex, ray, game);
		floor = get_pixel_color(game->image[IMG_FL], tex[Y], tex[X]);
		roof = get_pixel_color(game->image[IMG_RF], tex[Y], tex[X]);
		ft_put_pixel(x, y, floor, game);
		if (SCREEN_HEIGHT - y < MAPCELL * MAPGRID && x < MAPCELL * MAPGRID)
			continue ;
		ft_put_pixel(x, SCREEN_HEIGHT - y, roof, game);
	}
}

static void	draw_column(int x, int height, t_vector *ray, t_cubed *game)
{
	int		point[2];
	int32_t	color;

	point[A] = SCREEN_HEIGHT / 2 - height / 2 - 1;
	point[B] = SCREEN_HEIGHT / 2 + height / 2 - 1;
	if (height != SCREEN_HEIGHT)
		draw_background(x, point[B], ray, game);
	while (++point[A] < point[B])
	{
		color = get_pixel_color(game->image[ray->img], ray->x, ray->y);
		ray->y += ray->d;
		if (point[A] < MAPCELL * MAPGRID && x < MAPCELL * MAPGRID)
			continue ;
		ft_put_pixel(x, point[A], color, game);
	}
}

static void	calculate_texture(int *height, t_vector *ray, t_cubed *game)
{
	int map[2];

	get_map_position(map, ray->x, ray->y);
	if (ray->img == IMG_EA)
		ray->x = (int)(ray->y) % game->image[ray->img]->width;
	else
		ray->x = (int)(ray->x) % game->image[ray->img]->width;
	if (game->map->matrix[map[Y]][map[X]] == MAP_CLOSED)
		ray->img = IMG_DR;
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

void	draw_worldspace(t_cubed *game)
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
		calculate_texture(&height, &ray, game);
		draw_column(column, height, &ray, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		column++;
	}
}

/* static void	draw_background(int start, int end, int x, t_cubed *game) */
/* { */
/* 	int	floor; */
/* 	int	roof; */
/**/
/* 	roof = -1; */
/* 	while (++roof < start) */
/* 	{ */
/* 		if (roof < MAPCELL * MAPGRID && x < MAPCELL * MAPGRID) */
/* 			continue ; */
/* 		ft_put_pixel(x, roof, game->color[COL_C], game); */
/* 	} */
/* 	floor = SCREEN_HEIGHT + 1; */
/* 	while (--floor > end) */
/* 		ft_put_pixel(x, floor, game->color[COL_F], game); */
/* } */
