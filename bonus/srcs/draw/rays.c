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

#include <cubed.h>

static float	get_collosion_point(t_vector *ray, t_camera *cam, t_cubed *game)
{
	int	map[2];

	while (true)
	{
		get_map_position(map, ray->x, ray->y);
		if (map[X] < 0 || map[X] >= game->map->width
			|| map[Y] < 0 || map[Y] >= game->map->height)
			break ;
		else if (ft_strchr(CHARSET_WALL,
				get_map_element(map[X], map[Y], game)))
			break ;
		ray->x += cam->dx;
		ray->y += cam->dy;
	}
	return (sqrtf(powf((ray->x - cam->x), 2) + powf((ray->y - cam->y), 2)));
}

static float	calc_vertical(
	t_vector *ray, t_camera *cam, float angle, t_cubed *game)
{
	float	ntan;

	ntan = -tan(angle);
	if (angle > NORTH && angle < SOUTH)
	{
		ray->x = (int)cam->x / CELLSIZE * CELLSIZE - 0.001f;
		cam->dx = -CELLSIZE;
	}
	else
	{
		ray->x = (int)cam->x / CELLSIZE * CELLSIZE + CELLSIZE;
		cam->dx = CELLSIZE;
	}
	ray->y = (cam->x - ray->x) * ntan + cam->y;
	cam->dy = -cam->dx * ntan;
	return (get_collosion_point(ray, cam, game));
}

static float	calc_horizontal(
	t_vector *ray, t_camera *cam, float angle, t_cubed *game)
{
	float	atan;

	atan = 1 / -tan(angle);
	if (angle > WEST)
	{
		ray->y = (int)cam->y / CELLSIZE * CELLSIZE - 0.001f;
		cam->dy = -CELLSIZE;
	}
	else
	{
		ray->y = (int)cam->y / CELLSIZE * CELLSIZE + CELLSIZE;
		cam->dy = CELLSIZE;
	}
	ray->x = (cam->y - ray->y) * atan + cam->x;
	cam->dx = -cam->dy * atan;
	return (get_collosion_point(ray, cam, game));
}

void	calculate_ray(t_vector *ray, t_camera *cam, t_cubed *game)
{
	t_vector	horizontal;
	t_vector	vertical;

	horizontal.d = calc_horizontal(&horizontal, cam, ray->a, game);
	vertical.d = calc_vertical(&vertical, cam, ray->a, game);
	if (horizontal.d < vertical.d)
	{
		ray->x = horizontal.x;
		ray->y = horizontal.y;
		ray->d = horizontal.d;
		ray->img = IMG_SO;
	}
	else
	{
		ray->x = vertical.x;
		ray->y = vertical.y;
		ray->d = vertical.d;
		ray->img = IMG_EA;
	}
}
