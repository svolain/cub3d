/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:08:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/20 18:54:16 by jmertane         ###   ########.fr       */
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
	t_vector *horizon, t_vector *vec, t_mapinfo *map)
{
	float	offset[2];
	float	atan;

	atan = 1 / -tan(vec->a);
	/* printf("atan is: %f veca is: %f\n", atan, vec->a); */
	if (vec->a > WEST)
	{
		horizon->y = (int)vec->y / CELLSIZE * CELLSIZE - 0.0001f;
		offset[Y] = -CELLSIZE;
	}
	else
	{
		horizon->y = (int)vec->y / CELLSIZE * CELLSIZE + CELLSIZE;
		offset[Y] = CELLSIZE;
	}
	horizon->x = (vec->y - horizon->y) * atan + vec->x;
	offset[X] = -offset[Y] * atan;
	find_collosion_point(horizon, offset, map);
	return (sqrtf(powf((horizon->x - vec->x), 2) + powf((horizon->y - vec->y), 2)));
}

static float	vertical_collosion(
	t_vector *vertical, t_vector *vec, t_mapinfo *map)
{
	float	offset[2];
	float	ntan;

	ntan = -tan(vec->a);
	/* printf("ntan is: %f veca is: %f\n", ntan, vec->a); */
	if (vec->a > NORTH && vec->a < SOUTH)
	{
		vertical->x = (int)vec->x / CELLSIZE * CELLSIZE - 0.0001f;
		offset[X] = -CELLSIZE;
	}
	else
	{
		vertical->x = (int)vec->x / CELLSIZE * CELLSIZE + CELLSIZE;
		offset[X] = CELLSIZE;
	}
	vertical->y = (vec->x - vertical->x) * ntan + vec->y;
	offset[Y] = -offset[X] * ntan;
	find_collosion_point(vertical, offset, map);
	return (sqrtf(powf((vertical->x - vec->x), 2) + powf((vertical->y - vec->y), 2)));
}

static void	calculate_ray(t_vector *vec, t_mapinfo *map)
{
	t_vector	horizontal;
	t_vector	vertical;
	float		distance[2];

	/* printf("veca in calculate_ray is: %f\n", vec->a); */
	distance[H] = horizontal_collosion(&horizontal, vec, map);
	distance[V] = vertical_collosion(&vertical, vec, map);
	/* printf("disth = %f distv = %f\n", distance[H], distance[V]); */
	if (distance[H] < distance[V])
	{
		vec->x = horizontal.x;
		vec->y = horizontal.y;
		vec->dist = distance[H];
		/* printf("camx = %f camy = %f vecx = %f vecy = %f angle = %f dist = %f\n" */
		/*  	, cam->x, cam->y, vec->x, vec->y, vec->a, vec->dist); */
	}
	else
	{
		vec->x = vertical.x;
		vec->y = vertical.y;
		vec->dist = distance[V];
		/* printf("camx = %f camy = %f vecx = %f vecy = %f angle = %f dist = %f\n" */
		/*  	, cam->x, cam->y, vec->x, vec->y, vec->a, vec->dist); */
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
	vec = safe_calloc(sizeof(t_vector), game);
	i = 0;
	while (i < 66)
	{
		vec->a = angle;
		/* printf("veca in calculate_rays is: %f\n", vec->a); */
		update_rotation(&angle, DEGREE, ROTATE_RIGHT);
		calculate_ray(vec, game->map);
		printf("iter[%d] x = %f y = %f dist = %f angle = %f\n"
		, i, vec->x, vec->y, vec->dist, vec->a);
		draw_walls(game, vec, i);
		i++;
	}
	free(vec);
}

// calculate_ray(&vec, game->cam, game->map);
// game->map->endx = vec.x;
// game->map->endy = vec.y;

/*mlx_image_t		*t;
t = mlx_new_image(game->mlx, 8, 8);
ft_memset(t->pixels, 166, t->width * t->height * BPP);
mlx_image_to_window(game->mlx, t, vec.x, vec.y); */
