/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/25 13:04:04 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static	void	draw_rays(t_cubed *game, int endx, int endy)
{
	float	deltaX;
	float	deltaY;
	int		pixels;
	float	pixelX;
	float	pixelY;

	deltaX = endx / 2 - game->map->mplayer->instances[0].x;
	deltaY = endy / 2 - game->map->mplayer->instances[0].y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = game->map->mplayer->instances[0].x;
	pixelY = game->map->mplayer->instances[0].y;
	while(pixels)
	{
		if (pixelY >= 255)
			pixelY = 255;
		if (pixelY < 0)
			pixelY = 0;
		if (pixelX >= 255)
			pixelX = 255;
		if (pixelX < 0)
			pixelX = 0;	
		if (game->map->msfloor == NULL)
			mlx_put_pixel(game->map->mfloor, (int)pixelX, (int)pixelY, 160);
		else
			mlx_put_pixel(game->map->msfloor, (int)pixelX, (int)pixelY, 160);
		pixelX += deltaX;
    	pixelY += deltaY;
    	--pixels;
	}
}

void	calculate_rays(t_cubed *game)
{
	t_vector	*ray;
	float		angle;
	int			i;

	change_mini_foor(game);
	draw_minimap(game, 1);
	angle = game->cam->a;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	ray = safe_calloc(sizeof(t_vector), game);
	i = 0;
	while (i < 66)
	{
		ray->a = angle;
		calculate_ray(ray, game);
		ft_rotate(&angle, DEGREE, ROTATE_RIGHT);
		draw_rays(game, ray->x, ray->y);
		i++;
	}
	free(ray);
}

void	change_mini_foor(t_cubed *game)
{
	mlx_image_t		*floor;

	if (game->map->msfloor == NULL)
	{
		mlx_delete_image(game->mlx, game->map->mfloor);
		game->map->mfloor = NULL;
		floor = mlx_new_image(game->mlx, CELLSIZE * 4, CELLSIZE * 4);
		ft_memset(floor->pixels, 220, floor->width * floor->height * BPP);
		game->map->msfloor = floor;
	}
	else
	{
		mlx_delete_image(game->mlx, game->map->msfloor);
		game->map->msfloor = NULL;
		floor = mlx_new_image(game->mlx, CELLSIZE * 4, CELLSIZE * 4);
		ft_memset(floor->pixels, 220, floor->width * floor->height * BPP);
		game->map->mfloor = floor;
	}
}

void	move_minimap(t_cubed *game, t_action action)
{
	calculate_rays(game);

	if (action == MOVE_UP)
		game->map->mplayer->instances[0].y -= STEP_MOVEMENT / 2;
	else if (action == MOVE_DOWN)
		game->map->mplayer->instances[0].y += STEP_MOVEMENT / 2;
	else if (action == MOVE_LEFT)
		game->map->mplayer->instances[0].x -= STEP_MOVEMENT / 2;
	else if (action == MOVE_RIGHT)
		game->map->mplayer->instances[0].x += STEP_MOVEMENT / 2;
}

void	draw_minimap(t_cubed *game, int flag)
{
	int				i;
	int				j;
	mlx_image_t 	*floor;

	i = 0;
	if (game->map->msfloor == NULL)
		floor = game->map->mfloor;
	else
		floor = game->map->msfloor;
	mlx_image_to_window(game->mlx, floor, 0, 0);
	while (i < MINIMAP_MAX && i < game->map->height)
	{
		j = 0;
		while(j < MINIMAP_MAX && j < game->map->width)
		{
			if(game->map->matrix[i][j] == '1')
				mlx_image_to_window(game->mlx, game->map->mwall, j * CELLSIZE / 2, i * CELLSIZE / 2);
			j++;
		}
		i++;
	}
	if (flag == 0)
		mlx_image_to_window(game->mlx, game->map->mplayer, game->cam->x / 2, game->cam->y / 2);
}

void	init_minimap(t_cubed *game)
{
	mlx_image_t 	*player;
	mlx_image_t 	*wall;
	mlx_image_t		*floor;
	mlx_image_t 	*sfloor;

	sfloor = NULL;
	player = mlx_new_image(game->mlx, 8, 8);
	ft_memset(player->pixels, 255, player->width * player->height * BPP);
	wall = mlx_new_image(game->mlx, CELLSIZE / 2 - 2, CELLSIZE / 2 - 2);
	ft_memset(wall->pixels, 255, wall->width * wall->height * BPP);
	floor = mlx_new_image(game->mlx, CELLSIZE * 4, CELLSIZE * 4);
	ft_memset(floor->pixels, 220, floor->width * floor->height * BPP);
	game->map->mplayer = player;
	game->map->mwall = wall;
	game->map->mfloor = floor;
	game->map->msfloor = sfloor;
	draw_minimap(game, 0);
}

 