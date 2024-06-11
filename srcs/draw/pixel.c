/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:17:16 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 15:41:43 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static bool	ft_istransparent(uint32_t color)
{
	if (!get_channel_color(color, GET_ALPHA))
		return (true);
	return (false);
}

static int	valid_pixel(mlx_image_t *img, uint32_t x, uint32_t y)
{
	return (x < img->width && y < img->height);
}

int32_t	get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y)
{
	uint8_t	*start;

	if (!valid_pixel(img, x, y))
		return (0xFF000000);
	start = img->pixels + (y * img->width + x) * BPP;
	return (get_rgba(*start, *(start + 1), *(start + 2), *(start + 3)));
}

void	ft_put_pixel(int x, int y, int32_t color, t_cubed *game)
{
	if (!valid_pixel(game->canvas, x, y) || ft_istransparent(color)
		|| get_pixel_color(game->canvas, x, y) == color)
		return ;
	mlx_put_pixel(game->canvas, x, y, color);
}

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
