/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/15 10:01:11 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	draw_ray(t_vector *ray, t_camera *cam, t_cubed *game)
{
	ray->d /= MAPSCALE;
	cam->dx = (ray->x - cam->x) / ray->d / MAPSCALE;
	cam->dy = (ray->y - cam->y) / ray->d / MAPSCALE;
	ray->x = MAPSIZE / 2;
	ray->y = MAPSIZE / 2;
	while (ray->d >= 0)
	{
		ft_put_pixel(ray->x, ray->y, COLOR_RAY, game->image[IMG_MR]);
		ray->x += cam->dx;
		ray->y += cam->dy;
		ray->d--;
	}
}

void	draw_fov(t_camera *cam, float angle, t_cubed *game)
{
	static int	max_fov = 66;
	static int	density = 5;
	t_vector	ray;
	int			i;

	i = 0;
	ft_memset(game->image[IMG_MR]->pixels,
		0, game->image[IMG_MR]->height
		* game->image[IMG_MR]->width * BPP);
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (i < density * max_fov)
	{
		ray.a = angle;
		calculate_ray(&ray, cam, game, CHARSET_WALL);
		draw_ray(&ray, cam, game);
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
	cam_y -= MAPGRID / 2 * CELLSIZE;
	while (row < MAPSIZE)
	{
		if (column < MAPBORDER || column > MAPSIZE - MAPBORDER
			|| row < MAPBORDER || row > MAPSIZE - MAPBORDER)
			color = COLOR_BORDER;
		else if (column % MAPCELL == 0 || row % MAPCELL == 0)
			color = COLOR_GRID;
		else
			color = get_map_color(cam_x, cam_y, game);
		ft_put_pixel(column, row, color, game->image[IMG_MM]);
		cam_y += MAPSCALE;
		row++;
	}
}

void	draw_minimap(int cam_x, int cam_y, t_cubed *game)
{
	int	column;

	column = 0;
	cam_x -= MAPGRID / 2 * CELLSIZE;
	while (column < MAPSIZE)
	{
		draw_column(column, cam_x, cam_y, game);
		cam_x += MAPSCALE;
		column++;
	}
}
