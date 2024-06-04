/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:35 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/04 19:13:57 by jmertane         ###   ########.fr       */
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

void	animate_torch(t_cubed *game)
{
	static int	i = 0;
	mlx_image_t	*old;
	mlx_image_t	*new;

	old = game->anim[IMG_TO];
	i++;
	if (i > 5)
		i = 0;
	new = game->anim[i];
	ft_memcpy(old->pixels, new->pixels, old->height * old->width * BPP);
}

void	draw_torch(t_cubed *game)
{
	int x;
	int y;

	x = SCREEN_WIDTH / 2 - 100;
	y = SCREEN_HEIGHT - 330;
	safe_draw(game->anim[IMG_TO], x, y, game);
}
