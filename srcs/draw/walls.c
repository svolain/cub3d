/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:35:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/18 22:04:22 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	draw_space(int start_point, int end_point, int x, t_cubed *game)
{
	int	floor;
	int	roof;

	roof = -1;
	floor = SCREEN_HEIGHT + 1;
	while (roof++ < start_point)
		ft_putpixel(x, roof, game->col[COL_C], game);
	while (floor-- > end_point)
		ft_putpixel(x, floor, game->col[COL_F], game);
}

static void	draw_column(int height, int x, t_cubed *game)
{
	int32_t	color;
	int		point[2];
	int		repeat;
	int		i;

	point[Y_START] = SCREEN_HEIGHT / 2 - height / 2 - 1;
	point[Y_END] = SCREEN_HEIGHT / 2 + height / 2;
	draw_space(point[Y_START], point[Y_END], x, game);
	repeat = height / CELLSIZE;
	while (point[Y_START] < point[Y_END])
	{
		i = -1;
		color = 255;
		/* color = get_texture_color(game); */
		while (i < repeat && point[Y_START] < point[Y_END])
		{
			ft_putpixel(x, point[Y_START], color, game);
			point[Y_START]++;
			i++;
		}
	}
}

static void	fix_fisheye(t_vector *ray, t_cubed *game)
{
	float	angle;

	angle = game->cam->a;
	ft_rotate(&angle, ray->a, ROTATE_LEFT);
	ray->d *= cos(angle);
}

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
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		height = CELLSIZE * SCREEN_HEIGHT / ray.d;
		if (height > SCREEN_HEIGHT)
			height = SCREEN_HEIGHT;
		draw_column(height, column, game);
		column++;
	}
}

/* static int32_t	get_texture_color(t_cubed *game) */
/* { */
/* 	static int	y = 0; */
/* 	static int	x = 0; */
/**/
/* 	y++; */
/* 	if (y++ != 0 && y % CELLSIZE == 0) */
/* 		y = 0; */
/* 	x++; */
/* 	if (x != 0 && x % CELLSIZE == 0) */
/* 		x = 0; */
/* 	printf("%d , %d", x, y); */
/* 	return (get_pixel_color(game->img[ELEM_NO], x, y)); */
/* } */
