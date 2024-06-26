/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:05:02 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/24 11:56:49 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static void	draw_ray(t_vector *ray, t_camera *cam, t_cubed *game)
{
	static int	blend = 215;
	t_rgba		src;

	src.r = blend;
	src.a = blend;
	while (ray->d >= 0)
	{
		src.color = get_rgba(src.r--, 75, 75, src.a--);
		if (!ft_is_border(ray->x, ray->y))
			ft_put_pixel(ray->x, ray->y, src.color, game->asset[IMG_FV]);
		ray->x += cam->dx;
		ray->y += cam->dy;
		ray->d--;
	}
}

static void	calculate_draw(t_vector *ray, t_camera *cam)
{
	ray->d /= MAPSCALE;
	cam->dx = (ray->x - cam->x) / ray->d / MAPSCALE;
	cam->dy = (ray->y - cam->y) / ray->d / MAPSCALE;
	ray->x = MAPSIZE / 2;
	ray->y = MAPSIZE / 2;
}

static void	draw_transparent(float angle, t_camera *cam, t_cubed *game)
{
	t_vector	ray;

	ray.a = angle;
	calculate_ray(&ray, cam, game);
	calculate_draw(&ray, cam);
	ray.d = MAPSIZE / 2 + MAPCELL;
	while (ray.d >= 0)
	{
		if (ft_valid_pixel(game->asset[IMG_FV], ray.x, ray.y))
			mlx_put_pixel(game->asset[IMG_FV], ray.x, ray.y, TRANSPARENT);
		ray.x += cam->dx;
		ray.y += cam->dy;
		ray.d--;
	}
}

static void	transparent_void(int density, t_camera *cam, t_cubed *game)
{
	static float	multiplier = 5.7f;
	float			angle[2];
	int				i;

	i = 0;
	angle[A] = cam->a;
	angle[B] = cam->a;
	ft_rotate(&angle[A], FOV / 2 + STEP_ANGLE, ROTATE_LEFT);
	ft_rotate(&angle[B], FOV / 2 + STEP_ANGLE, ROTATE_RIGHT);
	while (i < multiplier * density)
	{
		draw_transparent(angle[A], cam, game);
		draw_transparent(angle[B], cam, game);
		ft_rotate(&angle[A], DEGREE / density, ROTATE_RIGHT);
		ft_rotate(&angle[B], DEGREE / density, ROTATE_LEFT);
		i++;
	}
}

void	draw_fov(t_camera *cam, float angle, t_cubed *game)
{
	static int	density = 3;
	t_vector	ray;
	int			i;

	i = 0;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	transparent_void(density, cam, game);
	while (i < density * FOV_IN_DEGREE)
	{
		ray.a = angle;
		draw_transparent(ray.a, cam, game);
		calculate_ray(&ray, cam, game);
		calculate_draw(&ray, cam);
		draw_ray(&ray, cam, game);
		ft_rotate(&angle, DEGREE / density, ROTATE_RIGHT);
		i++;
	}
}
