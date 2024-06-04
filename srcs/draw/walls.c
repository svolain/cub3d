/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:35:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/04 19:41:13 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

/* draw_floor(x, point[B], ray, game); */
/* static void	draw_floor(int x, int y, t_vector *ray, t_cubed *game) */
/* { */
/* 	int32_t	color; */
/* 	float	offset; */
/* 	float	ty; */
/* 	float	tx; */
/**/
/* 	offset = ray->d; */
/* 	ty = CELLSIZE - ray->y; */
/* 	tx = ray->x; */
/* 	while (y < SCREEN_HEIGHT) */
/* 	{ */
/* 		color = get_color(game->image[IMG_FL], ray->x, ty); */
/* 		ft_putpixel(x, y, color, game); */
/* 		ty += offset; */
/* 		tx += offset; */
/* 		y++; */
/* 	} */
/* } */

void	draw_walls(t_cubed *game)
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
		calculate_draw(&height, &ray, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		draw_segment(column, height, &ray, game);
		column++;
	}
}
