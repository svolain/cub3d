/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/20 15:29:03 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	draw_rays(t_cubed *game, int endx, int endy)
{
	float	deltaX;
	float	deltaY;
	int		pixels;
	float	pixelX;
	float	pixelY;
	
	deltaX = endx - game->map->mplayer->instances[0].x;
	deltaY = endy - game->map->mplayer->instances[0].y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = game->map->mplayer->instances[0].x;
	pixelY = game->map->mplayer->instances[0].y;
	while(pixels)
	{
		mlx_put_pixel(game->map->mfloor, pixelX, pixelY, 200);
		pixelX += deltaX;
    	pixelY += deltaY;
    	--pixels;
	}
}

void	move_minimap(t_cubed *game, t_action action)
{
	if (action == MOVE_UP)
		game->map->mplayer->instances[0].y -= STEP_MOVEMENT / 4;
	else if (action == MOVE_DOWN)
		game->map->mplayer->instances[0].y += STEP_MOVEMENT / 4;
	else if (action == MOVE_LEFT)
		game->map->mplayer->instances[0].x -= STEP_MOVEMENT / 4;
	else if (action == MOVE_RIGHT)
		game->map->mplayer->instances[0].x += STEP_MOVEMENT / 4;
	draw_rays(game, game->map->endx, game->map->endy);
}

void	draw_minimap(t_cubed *game)
{
	int py;
	int	i;
	int	j;

	i = 0;
	py = SCREEN_HEIGHT - game->cam->y / 2;
	mlx_image_to_window(game->mlx, game->map->mfloor, 0, MINIMAP_Y);
	while (i < MINIMAP_MAX && i < game->map->height)
	{
		j = 0;
		while(j < MINIMAP_MAX && j < game->map->width)
		{
			if(game->map->matrix[i][j] == '1')
				mlx_image_to_window(game->mlx, game->map->mwall, j * CELLSIZE / 2, MINIMAP_Y + i * CELLSIZE / 2);
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->mlx, game->map->mplayer, game->cam->x / 2, py);
}

void	init_minimap(t_cubed *game)
{
	mlx_image_t 	*player;
	mlx_image_t 	*wall;
	mlx_image_t		*floor;

	player = mlx_new_image(game->mlx, 8, 8);
	ft_memset(player->pixels, 255, player->width * player->height * BPP);
	wall = mlx_new_image(game->mlx, CELLSIZE / 2 - 2, CELLSIZE / 2 - 2);
	ft_memset(wall->pixels, 255, wall->width * wall->height * BPP);
	floor = mlx_new_image(game->mlx, CELLSIZE * 4, CELLSIZE * 4);
	ft_memset(floor->pixels, 200, floor->width * floor->height * BPP);
	game->map->mplayer = player;
	game->map->mwall = wall;
	game->map->mfloor = floor;
	draw_minimap(game);
}

