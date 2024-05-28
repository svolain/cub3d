/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/28 15:57:18 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

/*mlx_image_t	*mplayer;
mlx_image_t	*mwall;
mlx_image_t	*mfloor;
mlx_image_t	*msfloor;*/

/*void	check_pixel_limits(float *pixelX, float *pixelY)
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

static	void	draw_rays(t_vector	*ray)
{
	float	deltaX;
	float	deltaY;
	int		pixels;
	float	pixelX;
	float	pixelY;

	deltaX = ray->x / 2 - mplayer->instances[0].x;
	deltaY = ray->y / 2 - mplayer->instances[0].y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = mplayer->instances[0].x;
	pixelY = mplayer->instances[0].y;
	while(pixels)
	{
		check_pixel_limits(&pixelX, &pixelY);
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
		draw_rays(ray);
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
*/
/*
void	draw_minimap(t_cubed *game)
{
	int				i;
	int				j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while(j < game->map->width)
		{
			j++;
		}
		i++;
	}

}*/

void	init_minimap(t_cubed *game)
{
	mlx_image_t	*floor;

	floor = mlx_new_image(game->mlx, CELLSIZE * 5, CELLSIZE * 5);
	ft_memset(floor->pixels, 220, floor->width * floor->height * BPP);
	game->map->minimap = floor;
	mlx_image_to_window(game->mlx, floor, 0, 0);
	//draw_minimap(game);

}


