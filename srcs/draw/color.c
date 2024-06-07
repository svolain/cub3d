/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:09:24 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/07 10:12:10 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

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
