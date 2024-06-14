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

	pixel[X] = (float)MAPSIZE / MAPSCALE;
	pixel[Y] = (float)MAPSIZE / MAPSCALE;
	delta[X] = (ray->x - game->cam->x) / MAPSCALE;
	delta[Y] = (ray->y - game->cam->y) / MAPSCALE;
	pixels = ray->d / MAPSCALE;
	delta[X] /= pixels;
	delta[Y] /= pixels;
	while(--pixels >= 0)
	{
		color = get_alpha_blend(get_rgba(225, 100, 100, alpha--),
			get_pixel_color(game->image[IMG_MM], pixel[X], pixel[Y]));
		ft_put_pixel(pixel[X], pixel[Y], color, game->image[IMG_MM]);
		pixel[X] += delta[X];
		pixel[Y] += delta[Y];
	}
}

static void	draw_fov(t_camera *cam, float angle, t_cubed *game)
{
	static int	max_fov = 66;
	static int	density = 5;
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
	cam_y -= MAPSIZE;
	while (row < MAPSIZE)
	{
		if (column < 3 || column > MAPSIZE - 3 || row < 3 || row > MAPSIZE - 3)
			color = COLOR_BORDER;
		else if (column % (MAPCELL) == 0 || row % (MAPCELL) == 0)
			color = COLOR_GRID;
		else
			color = get_map_color(cam_x, cam_y, game);
		ft_put_pixel(column, row, color, game->image[IMG_MM]);
		cam_y += MAPSCALE;
		row++;
	}
}

void	draw_minimap(t_camera *cam, int cam_x, int cam_y, t_cubed *game)
{
	int	column;

	column = 0;
	cam_x -= MAPSIZE;
	while (column < MAPSIZE)
	{
		draw_column(column, cam_x, cam_y, game);
		cam_x += MAPSCALE;
		column++;
	}
	draw_fov(cam, cam->a, game);
}
