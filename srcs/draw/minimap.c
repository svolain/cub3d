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

static void	draw_ray(t_vector *ray, float alpha, t_cubed *game)
{
	float	delta[2];
	float	pixel[2];
	int		pixels;
	int32_t	color;

	pixel[X] = (float)MAPSIZE / SCALE_FACTOR;
	pixel[Y] = (float)MAPSIZE / SCALE_FACTOR;
	delta[X] = (ray->x - game->cam->x) / SCALE_FACTOR;
	delta[Y] = (ray->y - game->cam->y) / SCALE_FACTOR;
	pixels = ray->d / SCALE_FACTOR;
	delta[X] /= pixels;
	delta[Y] /= pixels;
	while(pixels-- >= 0)
	{
		color = get_alpha_blend(get_rgba(225, 100, 100, alpha--),
			get_pixel_color(game->canvas, pixel[X], pixel[Y]));
		ft_put_pixel(pixel[X], pixel[Y], color, game->minimap);
		pixel[X] += delta[X];
		pixel[Y] += delta[Y];
	}
}

static void	draw_fov(t_camera *cam, float angle, t_cubed *game)
{
	static int	max_fov = 66;
	static int	density = 3;
	t_vector	ray;
	int			i;

	i = 0;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (i < density * max_fov)
	{
		ray.a = angle;
		calculate_ray(&ray, cam, game);
		draw_ray(&ray, 255, game);
		ft_rotate(&angle, DEGREE / density, ROTATE_RIGHT);
		i++;
	}
}

static int32_t	get_map_color(int cam_x, int cam_y, t_cubed *game)
{
	int	map[2];

	get_map_position(map, cam_x, cam_y);
	if (map[X] < 0 || map[X] >= game->map->width
		|| map[Y] < 0 || map[Y] >= game->map->height)
		return (COLOR_WALL);
	else if (get_map_element(map[X], map[Y], game) == MAP_CLOSED)
		return (COLOR_DOOR_C);
	else if (get_map_element(map[X], map[Y], game) == MAP_OPENED)
		return (COLOR_DOOR_O);
	else if (get_map_element(map[X], map[Y], game) == MAP_FLOOR)
		return (COLOR_FLOOR);
	else
		return (COLOR_WALL);
}

static void	draw_column(int column, int cam_x, int cam_y, t_cubed *game)
{
	int32_t	color;
	int		row;

	row = 0;
	cam_y -= (float)MAPSIZE;
	while (row < MAPSIZE)
	{
		if (column % MAPCELL > 30 || row % MAPCELL > 30)
			color = COLOR_GRID;
		else
			color = get_map_color(cam_x, cam_y, game);
		ft_put_pixel(column, row, color, game->minimap);
		cam_y += SCALE_FACTOR;
		row++;
	}
}

void	draw_minimap(int cam_x, int cam_y, t_cubed *game)
{
	int			column;

	column = 0;
	cam_x -= (float)MAPSIZE;
	while (column < MAPSIZE)
	{
		draw_column(column, cam_x, cam_y, game);
		cam_x += SCALE_FACTOR;
		column++;
	}
}

void	*render_minimap(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, &game->mtx[MTX_CAM], game);
		draw_minimap(cam.x, cam.y, game);
		draw_fov(&cam, cam.a, game);
	}
	return (NULL);
}
