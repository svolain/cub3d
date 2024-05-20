/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:08:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/20 16:44:55 by jmertane         ###   ########.fr       */
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
	// printf("disth = %f distv = %f\n", distance[H], distance[V]);
	if (distance[H] < distance[V])
	{
		vec->x = horizontal.x;
		vec->y = horizontal.y;
		vec->dist = distance[H];
		// printf("camx = %f camy = %f vecx = %f vecy = %f angle = %f dist = %f\n"
		// 	, cam->x, cam->y, vec->x, vec->y, vec->a, vec->dist);
	}
	else
	{
		vec->x = vertical.x;
		vec->y = vertical.y;
		vec->dist = distance[V];
		// printf("camx = %f camy = %f vecx = %f vecy = %f angle = %f dist = %f\n"
		// 	, cam->x, cam->y, vec->x, vec->y, vec->a, vec->dist);
	}
}

void	calculate_rays(t_cubed *game)
{
	float		angle;
	t_vector	*vec;
	int			i;

	draw_floor(game);
	draw_minimap(game);
	angle = game->cam->a;
	update_rotation(&angle, FOV / 2, ROTATE_LEFT);
	i = 0;
	while (i < 66)
	{
		update_rotation(&angle, DEGREE, ROTATE_RIGHT);
		vec = safe_calloc(sizeof(t_vector), game);
		vec->a = angle;
		calculate_ray(vec, game->cam, game->map);
		printf("iter[%d] x = %f y = %f dist = %f angle = %f\n"
			, i, vec->x, vec->y, vec->dist, angle);
		draw_walls(game, vec);
		free(vec);
		i++;
	}

	// calculate_ray(&vec, game->cam, game->map);
	// game->map->endx = vec.x;
	// game->map->endy = vec.y;

	/*mlx_image_t		*t;
	t = mlx_new_image(game->mlx, 8, 8);
	ft_memset(t->pixels, 166, t->width * t->height * BPP);
	mlx_image_to_window(game->mlx, t, vec.x, vec.y); */
}
