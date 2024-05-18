/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/18 14:15:14 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void init_minimap(t_cubed *game)
{
	mlx_image_t 	*player;
	mlx_image_t 	*wall;
	mlx_image_t		*img;
	int i = 0;
	int j = 0;

	player = mlx_new_image(game->mlx, 8, 8);
	ft_memset(player->pixels, 200, player->width * player->height * BPP);
	wall = mlx_new_image(game->mlx, CELLSIZE / 2 - 2, CELLSIZE / 2 - 2);
	ft_memset(wall->pixels, 255, wall->width * wall->height * BPP);
	img = mlx_new_image(game->mlx, CELLSIZE * 4, CELLSIZE * 4);
	ft_memset(img->pixels, 200, img->width * img->height * BPP);
	mlx_image_to_window(game->mlx, img, SCREEN_WIDTH - CELLSIZE * 4, SCREEN_HEIGHT - CELLSIZE * 4);
	while (i < 8)
	{
		j = 0;
		while(j < 8)
		{
			if(game->map->matrix[i][j] == '1')
				mlx_image_to_window(game->mlx, wall, SCREEN_WIDTH - CELLSIZE * 4 + j * CELLSIZE / 2, SCREEN_HEIGHT - CELLSIZE * 4 + i * CELLSIZE / 2);
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->mlx, player, game->cam->x, game->cam->y);
}

