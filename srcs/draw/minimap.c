/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/25 14:29:09 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

mlx_image_t	*mplayer;
mlx_image_t	*mwall;
mlx_image_t	*mfloor;
mlx_image_t	*msfloor;

static	void	draw_rays(int endx, int endy)
{
	float	deltaX;
	float	deltaY;
	int		pixels;
	float	pixelX;
	float	pixelY;

	deltaX = endx / 2 - mplayer->instances[0].x;
	deltaY = endy / 2 - mplayer->instances[0].y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = mplayer->instances[0].x;
	pixelY = mplayer->instances[0].y;
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
		if (msfloor == NULL)
			mlx_put_pixel(mfloor, (int)pixelX, (int)pixelY, 160);
		else
			mlx_put_pixel(msfloor, (int)pixelX, (int)pixelY, 160);
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
		draw_rays(ray->x, ray->y);
		i++;
	}
	free(ray);
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

void	draw_minimap(t_cubed *game, int flag)
{
	int				i;
	int				j;
	mlx_image_t 	*floor;

	i = 0;
	if (msfloor == NULL)
		floor = mfloor;
	else
		floor = msfloor;
	mlx_image_to_window(game->mlx, floor, 0, 0);
	while (i < MINIMAP_MAX && i < game->map->height)
	{
		j = 0;
		while(j < MINIMAP_MAX && j < game->map->width)
		{
			if(game->map->matrix[i][j] == '1')
				mlx_image_to_window(game->mlx, mwall, j * CELLSIZE / 2, i * CELLSIZE / 2);
			j++;
		}
		i++;
	}
	if (flag == 0)
		mlx_image_to_window(game->mlx, mplayer, game->cam->x / 2, game->cam->y / 2);
}

void	init_minimap(t_cubed *game)
{
	msfloor = NULL;
	mplayer = mlx_new_image(game->mlx, 8, 8);
	ft_memset(mplayer->pixels, 255, mplayer->width * mplayer->height * BPP);
	mwall = mlx_new_image(game->mlx, CELLSIZE / 2 - 2, CELLSIZE / 2 - 2);
	ft_memset(mwall->pixels, 255, mwall->width * mwall->height * BPP);
	mfloor = mlx_new_image(game->mlx, CELLSIZE * 4, CELLSIZE * 4);
	ft_memset(mfloor->pixels, 220, mfloor->width * mfloor->height * BPP);
	draw_minimap(game, 0);
}

 