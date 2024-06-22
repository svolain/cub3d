/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:05:02 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/21 10:05:14 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static int	ft_isborder(int x, int y)
{
	return (y < MAPBORDER || y > MAPSIZE - MAPBORDER
		|| x < MAPBORDER || x > MAPSIZE - MAPBORDER);
}

static void	draw_ray(t_rgba *src, t_vector *ray, t_camera *cam, t_cubed *game)
{
	while (ray->d >= 0)
	{
		src->color = get_rgba(src->r--, 75, 75, src->a--);
		if (!ft_isborder(ray->x, ray->y))
			ft_put_pixel(ray->x, ray->y, src->color, game->asset[IMG_FV]);
		ray->x += cam->dx;
		ray->y += cam->dy;
		ray->d--;
	}
}

static void	calculate_draw(t_rgba *src, t_vector *ray, t_camera *cam)
{
	static int	blend = 225;

	src->r = blend;
	src->a = blend;
	ray->d /= MAPSCALE;
	cam->dx = (ray->x - cam->x) / ray->d / MAPSCALE;
	cam->dy = (ray->y - cam->y) / ray->d / MAPSCALE;
	ray->x = MAPSIZE / 2;
	ray->y = MAPSIZE / 2;
}

void	draw_fov(t_camera *cam, float angle, t_cubed *game)
{
	static int	density = 6;
	t_vector	ray;
	t_rgba		src;
	int			i;

	i = 0;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (i < density * FOV_IN_DEG)
	{
		ray.a = angle;
		calculate_ray(&ray, cam, game, CHARSET_WALL);
		calculate_draw(&src, &ray, cam);
		draw_ray(&src, &ray, cam, game);
		ft_rotate(&angle, DEGREE / density, ROTATE_RIGHT);
		i++;
	}
}

	/* ft_memset(game->image[IMG_MR]->pixels, */
	/* 	0, game->image[IMG_MR]->height */
	/* 	* game->image[IMG_MR]->width * BPP); */
