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

/*mlx_image_t	*mplayer;
mlx_image_t	*mwall;
mlx_image_t	*mfloor;
mlx_image_t	*msfloor;

void	check_pixel_limits(float *pixelX, float *pixelY)
{
	if (*pixelY >= 255)
			*pixelY = 255;
		if (*pixelY < 0)
			*pixelY = 0;
		if (*pixelX >= 255)
			*pixelX = 255;
		if (*pixelX < 0)
			*pixelX = 0;
}

void	change_mini_foor(t_cubed *game)
{
	mlx_image_t		*floor;

	if (msfloor == NULL)
	{
		mlx_delete_image(game->mlx, mfloor);
		mfloor = NULL;
		floor = mlx_new_image(game->mlx, CELLSIZE * 4, CELLSIZE * 4);
		ft_memset(floor->pixels, 220, floor->width * floor->height * BPP);
		msfloor = floor;
	}
	else
	{
		mlx_delete_image(game->mlx, msfloor);
		msfloor = NULL;
		floor = mlx_new_image(game->mlx, CELLSIZE * 4, CELLSIZE * 4);
		ft_memset(floor->pixels, 220, floor->width * floor->height * BPP);
		mfloor = floor;
	}
}

void	move_minimap(t_cubed *game, t_action action)
{
	calculate_rays(game);

	if (action == MOVE_UP)
		mplayer->instances[0].y -= STEP_MOVEMENT / 2;
	else if (action == MOVE_DOWN)
		mplayer->instances[0].y += STEP_MOVEMENT / 2;
	else if (action == MOVE_LEFT)
		mplayer->instances[0].x -= STEP_MOVEMENT / 2;
	else if (action == MOVE_RIGHT)
		mplayer->instances[0].x += STEP_MOVEMENT / 2;
}

void	check_pixel(t_cubed *game, int x, int y)
{
	printf("x: %d | y: %d\n", x, y);


	if (x < 0 || x >= game->map->width
		|| y < 0 || y >= game->map->height)
		ft_putpixel(x, y, game->color[COL_MF], game);
	else if (game->map->matrix[y][x] == '0')
		ft_putpixel(x, y, game->color[COL_MF], game);
	else if (game->map->matrix[y][x] == '1')
		ft_putpixel(x, y, game->color[COL_MW], game);
}

void	draw_bllah(t_cubed *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x= game->cam->x / CELLSIZE;
	y= game->cam->y / CELLSIZE;
	//printf("x: %d | y: %d\n", x, y);
	i = 0;
	while (i < 5)
	{
		j = 0;
		while(j < 5)
		{
				check_pixel(game, x + j, y - i);
				check_pixel(game, x - j, y + i);
				check_pixel(game, x + j, y - i);
				check_pixel(game, x - j, y + i);
				j++;
		}
		i++;
	}

}*/

static void	get_ray(t_vector *ray, t_cubed *game)
{
	float	delta[2];
	float	pixel[2];
	int		pixels;
	float	blend;

	delta[X] = ray->x / SCALE_FACTOR - game->cam->x / SCALE_FACTOR;
	delta[Y] = ray->y / SCALE_FACTOR - game->cam->y / SCALE_FACTOR;
	pixels = sqrt((delta[X] * delta[X]) + (delta[Y] * delta[Y]));
	delta[X] /= pixels;
	delta[Y] /= pixels;
	pixel[X] = (MAPGRID / SCALE_FACTOR) * CELLSIZE / SCALE_FACTOR;
	pixel[Y] = (MAPGRID / SCALE_FACTOR) * CELLSIZE / SCALE_FACTOR;
	blend = 255;
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
	position = (MAPGRID / SCALE_FACTOR) * (CELLSIZE / SCALE_FACTOR) -10;
	player[X] = game->cam->x - (MAPGRID / SCALE_FACTOR) * CELLSIZE;
	//draw_player(game);
	while (column < MAPSIZE)
	{
		draw_column(column, player, game);
		player[X] += 2;
		column++;
	}
	draw_rays(game);
	safe_draw(game->image[IMG_MP], position, position, game);
}
