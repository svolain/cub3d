/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:35 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/17 19:56:43 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	animate_shotgun(t_cubed *game)
{
	//mlx_image_t	*frame_img;

	if (game->animation->active == 0)
		return ;
	game->animation->timer = game->mlx->delta_time;
	if (game->animation->timer < game->animation->delay)
		return ;
	game->animation->current_frame++;
	if (game->animation->current_frame == game->animation->frame_count)
	{
		game->animation->active = 0;
		game->animation->current_frame = 0;
	}
	if (game->animation->current_frame == 0)
		game->anim[IMG_G15]->instances->enabled = false;
	else
		game->anim[game->animation->current_frame - 1]->instances->enabled = false;
	game->anim[game->animation->current_frame]->instances->enabled = true;

	/*frame_img = game->anim[game->animation->current_frame];
	ft_memcpy(game->anim[IMG_GO], frame_img->pixels,
		frame_img->width * frame_img->height * sizeof(int32_t));*/
}

/*
void	wait_frame(t_cubed *game, float limit)
{
 	double	frame;

	frame = 0;
 	while (frame < limit)
		frame += game->mlx->delta_time * 1000;
	printf("frame: %f\n", frame);
}*/
/*
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
}*/
/*
void    animate_shotgun(t_cubed *game)
{
    //mlx_image_t *img;
	static int	i;
	write(1, "!\n", 2);
	i++;
	if (i < IMG_G2 || i > IMG_G15 + 1)
	 i = IMG_G2;
	if (i == IMG_G15 + 1)
	{
		game->anim[IMG_G15]->instances->enabled = false;
		game->anim[IMG_G1]->instances->enabled = true;
	}
	else
	{
		game->anim[i - 1]->instances->enabled = false;
		game->anim[i]->instances->enabled = true;
	}
	wait_frame(game, 100);
}*/