/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:08:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/16 15:25:17 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	find_collosion_point(
	t_vector *vec, float *offset, t_mapinfo *map)
{
	int	x;
	int	y;

	while (true)
	{
		x = vec->x / CELLSIZE;
		y = vec->y / CELLSIZE;
		if (x < 0 || x >= map->width
			|| y < 0 || y >= map->height
			|| map->matrix[y][x] != FLOOR)
			break ;
		vec->x += offset[X];
		vec->y += offset[Y];
	}
}

static float	horizontal_collosion(
	t_vector *vec, t_camera *cam, t_mapinfo *map)
{
	float	offset[2];
	float	atan;

	atan = 1 / -tan(vec->a);
	if (vec->a > WEST)
	{
		vec->y = (int)cam->y / CELLSIZE * CELLSIZE - 0.0001f;
		offset[Y] = -CELLSIZE;
	}
	else
	{
		vec->y = (int)cam->y / CELLSIZE * CELLSIZE + CELLSIZE;
		offset[Y] = CELLSIZE;
	}
	vec->x = (cam->y - vec->y) * atan + cam->x;
	offset[X] = -offset[Y] * atan;
	find_collosion_point(vec, offset, map);
	return (sqrtf(powf((vec->x - cam->x), 2) + powf((vec->y - cam->y), 2)));
}

static float	vertical_collosion(
	t_vector *vec, t_camera *cam, t_mapinfo *map)
{
	float	offset[2];
	float	ntan;

	ntan = -tan(vec->a);
	if (vec->a > NORTH && vec->a < SOUTH)
	{
		vec->x = (int)cam->x / CELLSIZE * CELLSIZE - 0.0001f;
		offset[X] = -CELLSIZE;
	}
	else
	{
		vec->x = (int)cam->x / CELLSIZE * CELLSIZE + CELLSIZE;
		offset[X] = CELLSIZE;
	}
	vec->y = (cam->x - vec->x) * ntan + cam->y;
	offset[Y] = -offset[X] * ntan;
	find_collosion_point(vec, offset, map);
	return (sqrtf(powf((vec->x - cam->x), 2) + powf((vec->y - cam->y), 2)));
}

static void	calculate_ray(t_vector *vec, t_camera *cam, t_mapinfo *map)
{
	t_vector	horizontal;
	t_vector	vertical;
	float		distance[2];

	distance[H] = horizontal_collosion(&horizontal, cam, map);
	distance[V] = vertical_collosion(&vertical, cam, map);
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
	t_texture	*tex;
	float		offset;
	int			i;

	i = 0;
	offset = game->cam->a - FOV / 2;
	while (i < 90)
	{
		tex = game->tex + i++;
		tex->vec->a = offset + DEGREE;
		calculate_ray(tex->vec, game->cam, game->map);
	}
}
