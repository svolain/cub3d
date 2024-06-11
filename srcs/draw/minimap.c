/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 15:41:31 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	draw_ray(t_vector *ray, t_cubed *game)
{
	float	delta[2];
	float	pixel[2];
	int		pixels;
	int		alpha;
	int32_t	color;

	alpha = 200;
	pixel[X] = (float)MAPSIZE / SCALE_FACTOR;
	pixel[Y] = (float)MAPSIZE / SCALE_FACTOR;
	delta[X] = (ray->x - game->cam->x) / SCALE_FACTOR;
	delta[Y] = (ray->y - game->cam->y) / SCALE_FACTOR;
	pixels = sqrt(powf(delta[X], 2) + powf(delta[Y], 2));
	delta[X] /= pixels;
	delta[Y] /= pixels;
	while(pixels-- >= 0)
	{
		color = get_alpha_blend(get_rgba(225, 100, 100, alpha--),
			get_pixel_color(game->canvas, pixel[X], pixel[Y]));
		ft_put_pixel(pixel[X], pixel[Y], color, game);
		pixel[X] += delta[X];
		pixel[Y] += delta[Y];
	}
}

static void	draw_fov(t_cubed *game)
{
	static int	max_fov = 66;
	static int	density = 5;
	t_vector	ray;
	float		angle;
	int			i;

	angle = get_float(&game->cam->a, &game->mtx[MTX_CAM], game);
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	i = 0;
	while (i < density * max_fov)
	{
		ray.a = angle;
		calculate_ray(&ray, game);
		draw_ray(&ray, game);
		ft_rotate(&angle, DEGREE / density, ROTATE_RIGHT);
		i++;
	}
}

static int32_t	get_map_color(int *player, t_cubed *game)
{
	int	map[2];

	get_map_position(map, player[X], player[Y]);
	if (map[X] < 0 || map[X] >= game->map->width
		|| map[Y] < 0 || map[Y] >= game->map->height)
		return (get_rgba(150, 150, 150, 150));
	else if (game->map->matrix[map[Y]][map[X]] == MAP_CLOSED)
		return (get_rgba(50, 150, 150, 255));
	else if (game->map->matrix[map[Y]][map[X]] == MAP_OPENED)
		return (get_rgba(100, 200, 50, 255));
	else if (game->map->matrix[map[Y]][map[X]] == MAP_FLOOR)
		return (get_rgba(255, 255, 255, 200));
	else
		return (get_rgba(150, 150, 150, 150));
}

static void	draw_column(int column, int *player, t_cubed *game)
{
	int32_t	color;
	int		row;

	row = 0;
	player[Y] = get_float(&game->cam->y, &game->mtx[MTX_CAM], game) - MAPSIZE;
	while (row < MAPSIZE)
	{
		if (column % MAPCELL > 30 || row % MAPCELL > 30)
			color = get_rgba(50, 50, 50, 200);
		else
			color = get_map_color(player, game);
		ft_put_pixel(column, row, color, game);
		player[Y] += SCALE_FACTOR;
		row++;
	}
}

void	draw_minimap(t_cubed *game)
{
	static int	position = MAPSIZE / SCALE_FACTOR - (MAPCELL / 2);
	int			player[2];
	int			column;

	column = 0;
	player[X] = get_float(&game->cam->x, &game->mtx[MTX_CAM], game) - MAPSIZE;
	while (column < MAPSIZE)
	{
		draw_column(column, player, game);
		player[X] += SCALE_FACTOR;
		column++;
	}
	draw_fov(game);
	image_to_canvas(position, position, game->image[IMG_PL], game);
}

void	*render_minimap(void *param)
{
	t_cubed	*game;

	game = param;
	while (!game_over(game))
		draw_minimap(game);
	return (NULL);
}
