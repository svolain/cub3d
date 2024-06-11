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

	point[A] = SCREEN_HEIGHT / 2 - height / 2 - 1;
	point[B] = SCREEN_HEIGHT / 2 + height / 2 - 1;
	shade = calculate_shade(height);
	while (++point[A] < point[B])
	{
		color = get_alpha_blend(shade,
			get_pixel_color(game->image[ray->img], ray->x, ray->y));
		ray->y += ray->d;
		if (point[A] < MAPCELL * MAPGRID && column < MAPCELL * MAPGRID)
			continue ;
		ft_put_pixel(column, point[A], color, game);
	}
}

static void	calculate_draw(int *height, t_vector *ray, t_cubed *game)
{
	int map[2];

	get_map_position(map, ray->x, ray->y);
	if (ray->img == IMG_EA)
		ray->x = (int)(ray->y) % game->image[ray->img]->width;
	else
		ray->x = (int)(ray->x) % game->image[ray->img]->width;
	if (game->map->matrix[map[Y]][map[X]] == MAP_CLOSED)
		ray->img = IMG_DR;
	else if (ray->img == IMG_EA && ray->a > NORTH && ray->a < SOUTH)
		ray->img = IMG_WE;
	else if (ray->img == IMG_SO && ray->a > WEST)
		ray->img = IMG_NO;
	ray->y = 0;
	ray->d = (float)game->image[ray->img]->width / *height;
	if (*height > SCREEN_HEIGHT)
	{
		ray->y = (float)(*height - SCREEN_HEIGHT) / 2 * ray->d;
		*height = SCREEN_HEIGHT;
	}
}

void	draw_worldspace(t_cubed *game)
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
		draw_column(column, height, &ray, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		column++;
	}
}

void	*render_worldspace(void *param)
{
	t_cubed	*game;

	game = param;
	while (!game_over(game))
		draw_worldspace(game);
	return (NULL);
}
