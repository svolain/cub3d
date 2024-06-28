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

#include <cubed_bonus.h>

static int32_t	get_map_color(int cam_x, int cam_y, t_cubed *game)
{
	int	map[2];

	if (!ft_inside_map(cam_x, cam_y, game))
		return (COLOR_WALL);
	get_map_position(map, cam_x, cam_y);
	if (get_map_element(map[X], map[Y], game) == MAP_CLOSED)
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
		if (ft_is_border(column, row))
			color = COLOR_BORDER;
		else if (ft_is_grid(column, row))
			color = COLOR_GRID;
		else
			color = get_map_color(cam_x, cam_y, game);
		ft_put_pixel(column, row, color, game->asset[IMG_MM]);
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
