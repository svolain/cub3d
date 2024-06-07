/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:24:05 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/05 21:05:06 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	image_to_canvas(int dst_x, int dst_y, mlx_image_t *img, t_cubed *game)
{
	uint32_t	color;
	uint32_t	height;
	uint32_t	i;
	uint32_t	j;

	i = 0;
	height = dst_y;
	while (i < img->width)
	{
		j = 0;
		dst_y = height;
		while (j < img->height)
		{
			color = get_pixel_color(img, i, j);
			ft_put_pixel(dst_x, dst_y, color, game);
			dst_y++;
			j++;
		}
		dst_x++;
		i++;
	}
}

void	draw_scene(void *param)
{
	t_cubed	*game;

	game = param;
	draw_minimap(game);
	draw_worldspace(game);
}
