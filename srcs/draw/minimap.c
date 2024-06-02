/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/31 15:26:42 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	get_ray(t_vector *ray, t_cubed *game)
{
	float	delta[2];
	float	pixel[2];
	int		pixels;
	int		blend;

	pixel[X] = MAPGRID / SCALE_FACTOR * CELLSIZE / SCALE_FACTOR;
	pixel[Y] = MAPGRID / SCALE_FACTOR * CELLSIZE / SCALE_FACTOR;
	delta[X] = ray->x / SCALE_FACTOR - game->cam->x / SCALE_FACTOR;
	delta[Y] = ray->y / SCALE_FACTOR - game->cam->y / SCALE_FACTOR;
	pixels = sqrt(powf(delta[X], 2) + powf(delta[Y], 2));
	delta[X] /= pixels;
	delta[Y] /= pixels;
	blend = 225;
	while(pixels)
	{
		ft_putpixel((int)pixel[X], (int)pixel[Y],
			get_rgba(225, 100, 100, blend--), game);
		pixel[X] += delta[X];
		pixel[Y] += delta[Y];
		--pixels;
	}
}

static void	draw_rays(t_cubed *game)
{
	t_vector	ray;
	float		angle;
	int			i;

	angle = game->cam->a;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	i = 0;
	while (i < 66)
	{
		ray.a = angle;
		calculate_ray(&ray, game);
		ft_rotate(&angle, DEGREE, ROTATE_RIGHT);
		get_ray(&ray, game);
		i++;
	}
}

static int32_t	get_map(int *player, t_cubed *game)
{
	int	x;
	int	y;

	x = player[X] / CELLSIZE;
	y = player[Y] / CELLSIZE;
	if (x < 0 || x >= game->map->width
		|| y < 0 || y >= game->map->height)
		return (game->color[COL_MW]);
	else if (game->map->matrix[y][x] == '0')
		return (game->color[COL_MF]);
	return (game->color[COL_MW]);
}

static void	draw_column(int column, int *player, t_cubed *game)
{
	int32_t	color;
	int		row;

	row = 0;
	player[Y] = game->cam->y - (MAPGRID / SCALE_FACTOR) * CELLSIZE;
	while (row < MAPSIZE)
	{
		if (column % MAPCELL > 30 || row % MAPCELL > 30)
			color = get_rgba(50, 50, 50, 200);
		else
			color = get_map(player, game);
		ft_putpixel(column, row, color, game);
		player[Y] += 2;
		row++;
	}
}

void	draw_minimap(t_cubed *game)
{
	int	column;
	int	player[2];
	int	position;
	
	column = 0;
	position = MAPGRID / SCALE_FACTOR * CELLSIZE / SCALE_FACTOR - 10;
	player[X] = game->cam->x - MAPGRID / SCALE_FACTOR * CELLSIZE;
	while (column < MAPSIZE)
	{
		draw_column(column, player, game);
		player[X] += 2;
		column++;
	}
	draw_rays(game);
	safe_draw(game->image[IMG_MP], position, position, game);
}
