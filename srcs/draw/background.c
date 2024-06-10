/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:23:09 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/10 11:23:12 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	calculate_draw(int row, float *tex, t_vector *ray, t_cubed *game)
{
	float	pp;
	float	dy;
	float	angle;

	angle = cos(fabs(game->cam->a - ray->a));
	pp = (float)SCREEN_WIDTH / tan(FOV / 2);
	dy = row - (float)SCREEN_HEIGHT / 2.0f;
	tex[X] = cos(ray->a) * pp * CELLSIZE / dy / angle;
	tex[Y] = sin(ray->a) * pp * CELLSIZE / dy / angle;
	tex[X] = (int)tex[X] % game->image[IMG_FL]->width;
	tex[Y] = (int)tex[Y] % game->image[IMG_FL]->height;
}

static void	draw_column(int column, int height, t_vector *ray, t_cubed *game)
{
	float	tex[2];
	int32_t	floor;
	int32_t	roof;

	int row = SCREEN_HEIGHT / 2 + height / 2 - 1;
	while (++row < SCREEN_HEIGHT)
	{
		calculate_draw(row, tex, ray, game);
		floor = get_pixel_color(game->image[IMG_FL], tex[X], tex[Y]);
		ft_put_pixel(column, row, floor, game);
		if (SCREEN_HEIGHT - row < MAPSIZE && column < MAPSIZE)
			continue ;
		roof = get_pixel_color(game->image[IMG_RF], tex[X], tex[Y]);
		ft_put_pixel(column, SCREEN_HEIGHT - row, roof, game);
	}
}

void	render_background(t_cubed *game)
{
	t_vector	ray;
	float		angle;
	int			height;
	int			column;

	column = 0;
	angle = game->cam->a;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (column < SCREEN_WIDTH)
	{
		ray.a = angle;
		calculate_ray(&ray, game);
		fix_fisheye(&ray, game);
		height = CELLSIZE * SCREEN_HEIGHT / ray.d;
		draw_column(column, height, &ray, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		column++;
	}
}

/* static void	draw_column(int column, int height, t_vector *ray, t_cubed *game) */
/* { */
/* 	int		point[2]; */
/* 	int32_t	color; */
/**/
/* 	point[A] = SCREEN_HEIGHT / 2 - height / 2 - 1; */
/* 	point[B] = SCREEN_HEIGHT / 2 + height / 2 - 1; */
/* 	if (height != SCREEN_HEIGHT) */
/* 		draw_background(column, point[B], ray, game); */
/* 	while (++point[A] < point[B]) */
/* 	{ */
/* 		color = get_pixel_color(game->image[ray->img], ray->x, ray->y); */
/* 		ray->y += ray->d; */
/* 		if (point[A] < MAPCELL * MAPGRID && column < MAPCELL * MAPGRID) */
/* 			continue ; */
/* 		color = get_alpha_blend(get_rgba(0, 0, 0, temp), color); */
/* 		ft_put_pixel(column, point[A], color, game); */
/* 	} */
/* } */
