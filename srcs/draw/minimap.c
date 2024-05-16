/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/15 20:51:10 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

mlx_image_t 	*player;
mlx_image_t 	*wall;
mlx_image_t		*img;
	int i = 0;
	int j = 0;

	player = mlx_new_image(mlx, 16, 16);
	ft_memset(player->pixels, 200, player->width * player->height * BPP);
	wall = mlx_new_image(mlx, CELLSIZE - 2, CELLSIZE - 2);
	ft_memset(wall->pixels, 255, wall->width * wall->height * BPP);
	while (i < 8)
	{
		j = 0;
		while(j < 8)
		{
			if(map[i][j] == '1')
				mlx_image_to_window(mlx, wall, j * CELLSIZE, i * CELLSIZE);
			j++;
		}
		i++;
	}
	mlx_image_to_window(mlx, player, px, py);
