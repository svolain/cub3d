/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:35 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/18 14:59:39 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	wait_frame(t_cubed *game, float limit)
{
 	double	frame;

	frame = 0;
 	while (frame < limit)
		frame += game->mlx->delta_time;
}

void	animate_shotgun(t_cubed *game)
{
	if (game->animation->active == 0)
		return ;
	game->animation->timer = game->mlx->delta_time;
	if (game->animation->timer < game->animation->delay)
		return ;;
	(*game->anim[game->animation->current_frame]).enabled = false;
	game->animation->current_frame += 1;
	game->animation->timer = 0;
	if (game->animation->current_frame == game->animation->frame_count)
	{
		game->animation->active = 0;
		game->animation->current_frame = IMG_GO;
		(*game->anim[IMG_GO]).enabled = true;
		return ;
	}
	(*game->anim[game->animation->current_frame]).enabled = true;
	wait_frame(game, 1000000);
}

void	draw_shotgun(t_cubed *game)
{

	int i = IMG_G15 + 1;
	while(--i > IMG_G1)
	{
		safe_draw(game->anim[i], 0, 0, game);
		(*game->anim[i]).enabled = false;
	}
	safe_draw(game->anim[IMG_GO], 0, 0, game);
}

void	init_animation(t_cubed *game)
{
	game->animation = safe_calloc(sizeof(t_anim), game);
	game->animation->active = 0;
	game->animation->delay = 0.02;
	game->animation->frame_count = GAME_ANIMS;
	game->animation->current_frame = IMG_GO;
}
