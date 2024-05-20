/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:35:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/18 22:04:22 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	draw_floor(t_cubed *game)
{
	mlx_image_t	*floord;
	mlx_image_t	*roofd;

	floord = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	color_image(floord, 200, 100, 0);
	mlx_image_to_window(game->mlx, floord, 0, SCREEN_HEIGHT / 2);
	roofd = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	color_image(roofd, 100, 200, 0);
	mlx_image_to_window(game->mlx, roofd, 0, 0);
}

void	draw_walls(t_cubed *game, t_vector *vec)
{
	mlx_image_t	*walld;
	float		height;

	height = CELLSIZE * SCREEN_HEIGHT / vec->dist;
	if (height > SCREEN_HEIGHT)
		height = SCREEN_HEIGHT;
	walld = mlx_new_image(game->mlx, 2, height);
	color_image(walld, 0, 100, 200);
	mlx_image_to_window(game->mlx, walld, vec->x, vec->y);
}
