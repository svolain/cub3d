/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:35 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/07 13:33:34 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	wait_frame(t_cubed *game, float limit)
{
 	double	frame;

	frame = 0;
 	while (frame < limit)
		frame += game->mlx->delta_time * 1000;
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

void    animate_shotgun(t_cubed *game, int i)
{
    mlx_image_t *old;
    mlx_image_t *new;

    old = game->anim[IMG_GO];
	//printf("i: %d\n", i);
	if (i == IMG_G15 + 1)
		new = game->anim[IMG_G1];
	else
		new = game->anim[i];
    ft_memcpy(old->pixels, new->pixels, old->height * old->width * BPP);
}