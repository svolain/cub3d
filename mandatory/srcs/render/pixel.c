/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:17:16 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/07 10:45:46 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

int32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
	if (!valid_pixel(game->canvas, x, y)
		|| get_pixel_color(game->canvas, x, y) == color)
		return ;
	mlx_put_pixel(game->canvas, x, y, color);
}
