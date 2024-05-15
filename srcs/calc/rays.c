/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:08:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/15 08:28:24 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	find_collosion_point(t_vec *vec, float *offset, t_map *map)
{
	int	x;
	int	y;

	while (true)
	{
		x = vec->x / CELLSIZE;
		y = vec->y / CELLSIZE;
		if (x < 0 || x >= map->width
			|| y < 0 || y >= map->height
			|| map[y][x] != FLOOR)
			break ;
		vec->x += offset[X];
		vec->y += offset[Y];
	}
}

static float	horizontal_collosion(t_vec *vec, t_map *map)
{
	float	offset[2];
	float	atan;

	vec->a = pa;
	atan = 1 / -tan(vec->a);
	if (vec->a > WEST)
	{
		vec->y = (int)py / CELLSIZE * CELLSIZE - 0.0001f;
		offset[Y] = -CELLSIZE;
	}
	else
	{
		vec->y = (int)py / CELLSIZE * CELLSIZE + CELLSIZE;
		offset[Y] = CELLSIZE;
	}
	vec->x = (py - vec->y) * atan + px;
	offset[X] = -offset[Y] * atan;
	find_collosion_point(vec, offset, map);
	return (sqrtf(powf((vec->x - px), 2) + powf((vec->y - py), 2)));
}

static float	vertical_collosion(t_vec *vec, t_map *map)
{
	float	offset[2];
	float	ntan;

	vec->a = pa;
	ntan = -tan(vec->a);
	if (vec->a > NORTH && vec->a < SOUTH)
	{
		vec->x = (int)px / CELLSIZE * CELLSIZE - 0.0001f;
		offset[X] = -CELLSIZE;
	}
	else
	{
		vec->x = (int)px / CELLSIZE * CELLSIZE + CELLSIZE;
		offset[X] = CELLSIZE;
	}
	vec->y = (px - vec->x) * ntan + py;
	offset[Y] = -offset[X] * ntan;
	find_collosion_point(vec, offset, map);
	return (sqrtf(powf((vec->x - px), 2) + powf((vec->y - py), 2)));
}

static void	calculate_ray(t_vec *vec, t_map *map)
{
	t_vec	horizontal;
	t_vec	vertical;
	float	distance[2];

	distance[H] = horizontal_collosion(&horizontal, map);
	distance[V] = vertical_collosion(&vertical, map);
	if (distance[H] < distance[V])
	{
		vec->x = horizontal.x;
		vec->y = horizontal.y;
	}
	else
	{
		vec->x = vertical.x;
		vec->y = vertical.y;
	}
}

void	calculate_rays(t_cubed *game)
{
	float	angle;
	float	offset[2];

	angle = game->cam->a;
}
