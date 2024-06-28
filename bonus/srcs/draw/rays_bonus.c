/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:08:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 15:04:02 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static void	update_ray_data(t_vector *vec, t_vector *ray, bool horizontal)
{
	ray->x = vec->x;
	ray->y = vec->y;
	ray->d = vec->d;
	if (horizontal)
		ray->img = IMG_SO;
	else
		ray->img = IMG_EA;
}

static void	get_collosion_point(t_vector *vec, t_camera *cam, t_cubed *game)
{
	while (true)
	{
		if (!ft_inside_map(vec->x, vec->y, game)
			|| ft_in_elements(vec->x, vec->y, CHARSET_WALL, game))
			break ;
		vec->x += cam->dx;
		vec->y += cam->dy;
	}
}

static void	calculate_vertical(t_vector *vec, t_camera *cam, float angle)
{
	float	ntan;

	ntan = -tan(angle);
	if (angle > NORTH && angle < SOUTH)
	{
		vec->x = (int)cam->x / CELLSIZE * CELLSIZE - 0.001f;
		cam->dx = -CELLSIZE;
	}
	else
	{
		vec->x = (int)cam->x / CELLSIZE * CELLSIZE + CELLSIZE;
		cam->dx = CELLSIZE;
	}
	vec->y = (cam->x - vec->x) * ntan + cam->y;
	cam->dy = -cam->dx * ntan;
}

static void	calculate_horizontal(t_vector *vec, t_camera *cam, float angle)
{
	float	atan;

	atan = 1 / -tan(angle);
	if (angle > WEST)
	{
		vec->y = (int)cam->y / CELLSIZE * CELLSIZE - 0.001f;
		cam->dy = -CELLSIZE;
	}
	else
	{
		vec->y = (int)cam->y / CELLSIZE * CELLSIZE + CELLSIZE;
		cam->dy = CELLSIZE;
	}
	vec->x = (cam->y - vec->y) * atan + cam->x;
	cam->dx = -cam->dy * atan;
}

void	calculate_ray(t_vector *ray, t_camera *cam, t_cubed *game)
{
	t_vector	vec[2];

	calculate_horizontal(&vec[H], cam, ray->a);
	get_collosion_point(&vec[H], cam, game);
	calculate_vertical(&vec[V], cam, ray->a);
	get_collosion_point(&vec[V], cam, game);
	vec[H].d = sqrtf(powf((vec[H].x - cam->x), 2)
			+ powf((vec[H].y - cam->y), 2));
	vec[V].d = sqrtf(powf((vec[V].x - cam->x), 2)
			+ powf((vec[V].y - cam->y), 2));
	if (vec[H].d < vec[V].d)
		update_ray_data(&vec[H], ray, true);
	else
		update_ray_data(&vec[V], ray, false);
}
