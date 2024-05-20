/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:28:59 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/20 16:34:33 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

int32_t	get_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	get_pixel(int32_t rgba, t_action action)
{
	if (action == GET_RED)
		return ((rgba >> 24) & 0xFF);
	else if (action == GET_GREEN)
		return ((rgba >> 16) & 0xFF);
	else if (action == GET_BLUE)
		return ((rgba >> 8) & 0xFF);
	else
		return (rgba & 0xFF);
}

void	color_image(mlx_image_t *image, int32_t r, int32_t g, int32_t b)
{
	int32_t		color;
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			color = get_rgba(r, g, b, 255);
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}

void	blend_alpha(mlx_image_t *image, int32_t alpha, uint32_t x, uint32_t y)
{
	int32_t	color;
	int32_t	r;
	int32_t	g;
	int32_t	b;

	r = get_pixel(*image->pixels, GET_RED);
	g = get_pixel(*image->pixels, GET_GREEN);
	b = get_pixel(*image->pixels, GET_BLUE);
	while (x < image->width)
	{
		y = 0;
		while (y < image->height)
		{
			color = get_rgba(r, g, b, alpha);
			mlx_put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}
