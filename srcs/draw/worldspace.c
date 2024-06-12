/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:35:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/10 11:23:14 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static int32_t	calculate_shade(int height)
{
	static int	treshold = 210;
	static int	modifier = 300;
	float		intensity;

	if (height <= treshold)
		return (get_rgba(0, 0, 0, 255));
	else
		intensity = (float)height / SCREEN_HEIGHT * 255.0f;
	return (get_rgba(0, 0, 0, modifier - intensity));
}

static void	draw_column(int column, int height, t_vector *ray, t_cubed *game)
{
	int		point[2];
	int32_t	shade;
	int32_t	color;

	shade = calculate_shade(height);
	point[A] = SCREEN_HEIGHT / 2 - height / 2;
	point[B] = SCREEN_HEIGHT / 2 + height / 2;
	while (++point[A] < point[B])
	{
		color = get_alpha_blend(shade, get_pixel_color
			(game->image[ray->img], ray->x, ray->y));
		ray->y += ray->d;
		if (point[A] < MAPSIZE && column < MAPSIZE)
			continue ;
		ft_put_pixel(column, point[A], color, game->canvas);
	}
}

static void	calculate_draw(int *height, t_vector *ray, t_cubed *game)
{
	int map[2];

	get_map_position(map, ray->x, ray->y);
	ray->d = (float)game->image[ray->img]->width / *height;
	if (ray->img == IMG_EA)
		ray->x = (int)(ray->y) % game->image[ray->img]->width;
	else
		ray->x = (int)(ray->x) % game->image[ray->img]->width;
	if (get_map_element(map[X], map[Y], game) == MAP_CLOSED)
		ray->img = IMG_DR;
	else if (ray->img == IMG_EA && ray->a > NORTH && ray->a < SOUTH)
		ray->img = IMG_WE;
	else if (ray->img == IMG_SO && ray->a > WEST)
		ray->img = IMG_NO;
	if (*height > SCREEN_HEIGHT)
	{
		ray->y = (float)(*height - SCREEN_HEIGHT) / 2 * ray->d;
		*height = SCREEN_HEIGHT;
	}
	else
		ray->y = 0;
}

void	draw_worldspace(t_camera *cam, float angle, t_cubed *game)
{
	t_vector	ray;
	int			height;
	int			column;

	column = 0;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (column < SCREEN_WIDTH)
	{
		ray.a = angle;
		calculate_ray(&ray, cam, game);
		fix_fisheye(&ray, cam->a);
		height = CELLSIZE * SCREEN_HEIGHT / ray.d;
		calculate_draw(&height, &ray, game);
		draw_column(column, height, &ray, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		column++;
	}
}

void	*render_worldspace(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, &game->mtx[MTX_CAM], game);
		draw_worldspace(&cam, cam.a, game);
	}
	return (NULL);
}
