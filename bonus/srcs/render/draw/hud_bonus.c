/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:56:17 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/28 14:14:51 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void    draw_hud(t_cubed *game)
{
    int height;
    int width;

    height = SCREEN_HEIGHT - HUD_HEIGHT;
    while(height == SCREEN_HEIGHT)
    {
        width = 0;
        while(width < SCREEN_WIDTH)
        {
            ft_put_pixel(width, height, COLOR_HUD, game->asset[IMG_HD]);
            width++;
        }
        height++;
    }
}
