/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:08:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/28 12:41:23 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	calc_collosion(t_vector *ray, float *offset, t_mapinfo *map)
{
	int	x;
	int	y;

	while (true)
	{
		x = ray->x / CELLSIZE;
		y = ray->y / CELLSIZE;
		if (x < 0 || x >= map->width
			|| y < 0 || y >= map->height - 1
			|| map->matrix[y][x] != MAP_FLOOR)
			break ;
		ray->x += offset[X_COOR];
		ray->y += offset[Y_COOR];
	}
}

static float	calc_horizontal(t_vector *ray, float angle, t_cubed *game)
{
	t_vector	*cam;
	float		offset[2];
	float		atan;

	cam = game->cam;
	atan = 1 / -tan(angle);
	if (angle > WEST)
	{
		ray->y = (int)cam->y / CELLSIZE * CELLSIZE - 0.0001f;
		offset[Y_COOR] = -CELLSIZE;
	}
	else
	{
		ray->y = (int)cam->y / CELLSIZE * CELLSIZE + CELLSIZE;
		offset[Y_COOR] = CELLSIZE;
	}
	ray->x = (cam->y - ray->y) * atan + cam->x;
	offset[X_COOR] = -offset[Y_COOR] * atan;
	calc_collosion(ray, offset, game->map);
	return (sqrtf(powf((ray->x - cam->x), 2) + powf((ray->y - cam->y), 2)));
}

static float	calc_vertical(t_vector *ray, float angle, t_cubed *game)
{
	t_vector	*cam;
	float		offset[2];
	float		ntan;

	cam = game->cam;
	ntan = -tan(angle);
	if (angle > NORTH && angle < SOUTH)
	{
		ray->x = (int)cam->x / CELLSIZE * CELLSIZE - 0.0001f;
		offset[X_COOR] = -CELLSIZE;
	}
	else
	{
		ray->x = (int)cam->x / CELLSIZE * CELLSIZE + CELLSIZE;
		offset[X_COOR] = CELLSIZE;
	}
	ray->y = (cam->x - ray->x) * ntan + cam->y;
	offset[Y_COOR] = -offset[X_COOR] * ntan;
	calc_collosion(ray, offset, game->map);
	return (sqrtf(powf((ray->x - cam->x), 2) + powf((ray->y - cam->y), 2)));
}

void	calculate_ray(t_vector *ray, t_cubed *game)
{
	t_vector	horizontal;
	t_vector	vertical;
	float		distance[2];

	distance[H_DIST] = calc_horizontal(&horizontal, ray->a, game);
	distance[V_DIST] = calc_vertical(&vertical, ray->a, game);
	if (distance[H_DIST] < distance[V_DIST])
	{
		ray->x = horizontal.x;
		ray->y = horizontal.y;
		ray->d = distance[H_DIST];
		ray->key = ELEM_WE;
	}
	else
	{
		ray->x = vertical.x;
		ray->y = vertical.y;
		ray->d = distance[V_DIST];
		ray->key = ELEM_NO;
	}
}
