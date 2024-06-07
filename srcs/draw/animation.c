/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:35 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/05 17:07:15 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	wait_frame(t_cubed *game, float limit)
{
 	double	frame;

	frame = 0;
 	while (frame < limit)
		frame += game->mlx->delta_time * 1000;
	frame -= limit;
}

void	animate_minimap(t_cubed *game)
{
	static int	i = 0;
	mlx_image_t	*old;
	mlx_image_t	*new;

	old = game->anim[IMG_MP];
	i++;
	if (i > 3)
		i = 0;
	new = game->anim[i];
	ft_memcpy(old->pixels, new->pixels, old->height * old->width * BPP);
}

void	animate_shotgun(t_cubed *game)
{
    static int  i;
    mlx_image_t *old;
    mlx_image_t *new;

    old = game->anim[IMG_TO];
    i++;
    if (i < 5 || i > 9)
        i = 5;
    new = game->anim[i];
    ft_memcpy(old->pixels, new->pixels, old->height * old->width * BPP);
}

void	draw_shotgun(t_cubed *game)
{
	int x;
	int y;

	x = SCREEN_WIDTH / 2 - 300;
	y = SCREEN_HEIGHT - 400;
	safe_draw(game->anim[IMG_TO], x, y, game);
}