/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:08:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/29 15:39:14 by vsavolai         ###   ########.fr       */
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
		if (x < 0 || x >= map->width || y < 0 || y >= map->height
			|| !ft_strchr(CHARSET_MOVEABLE, map->matrix[y][x]))
			break ;
		ray->x += offset[X];
		ray->y += offset[Y];
	}
}

static float	calc_horizontal(t_vector *ray, float angle, t_cubed *game)
{
	t_camera	*cam;
	float		offset[2];
	float		atan;

	cam = game->cam;
	atan = 1 / -tan(angle);
	if (angle > WEST)
	{
		ray->y = (int)cam->y / CELLSIZE * CELLSIZE - 0.0001f;
		offset[Y] = -CELLSIZE;
	}
	else
	{
		ray->y = (int)cam->y / CELLSIZE * CELLSIZE + CELLSIZE;
		offset[Y] = CELLSIZE;
	}
	ray->x = (cam->y - ray->y) * atan + cam->x;
	offset[X] = -offset[Y] * atan;
	calc_collosion(ray, offset, game->map);
	return (sqrtf(powf((ray->x - cam->x), 2) + powf((ray->y - cam->y), 2)));
}

static float	calc_vertical(t_vector *ray, float angle, t_cubed *game)
{
	t_camera	*cam;
	float		offset[2];
	float		ntan;

	cam = game->cam;
	ntan = -tan(angle);
	if (angle > NORTH && angle < SOUTH)
	{
		ray->x = (int)cam->x / CELLSIZE * CELLSIZE - 0.0001f;
		offset[X] = -CELLSIZE;
	}
	else
	{
		ray->x = (int)cam->x / CELLSIZE * CELLSIZE + CELLSIZE;
		offset[X] = CELLSIZE;
	}
	ray->y = (cam->x - ray->x) * ntan + cam->y;
	offset[Y] = -offset[X] * ntan;
	calc_collosion(ray, offset, game->map);
	return (sqrtf(powf((ray->x - cam->x), 2) + powf((ray->y - cam->y), 2)));
}

void	calculate_ray(t_vector *ray, t_cubed *game)
{
	t_vector	horizontal;
	t_vector	vertical;
	float		distance[2];

	distance[H] = calc_horizontal(&horizontal, ray->a, game);
	distance[V] = calc_vertical(&vertical, ray->a, game);
	if (distance[H] < distance[V])
	{
		ray->x = horizontal.x;
		ray->y = horizontal.y;
		ray->d = distance[H];
		ray->img = IMG_SO;
	}
	else
	{
		ray->x = vertical.x;
		ray->y = vertical.y;
		ray->d = distance[V];
		ray->img = IMG_EA;
	}
}
