/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:35:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/18 13:38:46 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

mlx_image_t 	*walld;

void	draw_walls(t_cubed *game, t_vector *vec)
{
	float	height;

	height = CELLSIZE * SCREEN_HEIGHT / vec->dist;
	if (height > SCREEN_HEIGHT)
		height = SCREEN_HEIGHT;
	walld = mlx_new_image(game->mlx, CELLSIZE / 2 - 2, CELLSIZE / 2 - 2);
	ft_memset(walld->pixels, 255, walld->width * walld->height * BPP);
}
