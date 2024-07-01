/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/30 11:47:34 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static int32_t	get_map_color(int cam_x, int cam_y, t_cubed *game)
{
	int		map[2];
	char	c;

	if (!ft_inside_map(cam_x, cam_y, game))
		return (COLOR_WALL);
	get_map_position(map, cam_x, cam_y);
	c = get_map_element(map[X], map[Y], game);
	if (c == MAP_CLOSED)
		return (COLOR_DOOR_C);
	else if (c == MAP_OPENED)
		return (COLOR_DOOR_O);
	else if (c == MAP_FLOOR)
		return (COLOR_FLOOR);
	else if (c == MAP_AMMO
		|| c == MAP_HEALTH)
		return (COLOR_PICKUP);
	else if (c == MAP_EXIT)
		return (COLOR_EXIT);
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
