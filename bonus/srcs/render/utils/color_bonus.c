/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:09:24 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/08 18:52:51 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

int32_t	get_channel_color(int32_t rgba, t_action action)
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

int32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int32_t	calculate_blend(t_rgba src, t_rgba dst)
{
	t_rgba	out;
	float	src_a;
	float	dst_a;

	src_a = src.a / 255.0f;
	dst_a = dst.a / 255.0f;
	out.r = (src.r * src_a) + (dst.r * dst_a * (1 - src_a));
	out.g = (src.g * src_a) + (dst.g * dst_a * (1 - src_a));
	out.b = (src.b * src_a) + (dst.b * dst_a * (1 - src_a));
	out.a = (src_a + dst_a * (1 - src_a)) * 255.0f;
	return (get_rgba(out.r, out.g, out.b, out.a));
}

int32_t	get_alpha_blend(int32_t source, int32_t destination)
{
	t_rgba	src;
	t_rgba	dst;

	src.r = get_channel_color(source, GET_RED);
	src.g = get_channel_color(source, GET_GREEN);
	src.b = get_channel_color(source, GET_BLUE);
	src.a = get_channel_color(source, GET_ALPHA);
	dst.r = get_channel_color(destination, GET_RED);
	dst.g = get_channel_color(destination, GET_GREEN);
	dst.b = get_channel_color(destination, GET_BLUE);
	dst.a = get_channel_color(destination, GET_ALPHA);
	return (calculate_blend(src, dst));
}
