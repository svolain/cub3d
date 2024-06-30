/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:35 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/30 11:46:59 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	wait_frame(t_cubed *game, float limit)
{
	double	frame;

	frame = 0;
	while (frame < limit * 1000)
		frame += game->mlx->delta_time;
}

void	loop_portal(t_sprite *spr, t_cubed *game)
{
	(*spr->frame[spr->current_frame]).enabled = false;
	safe_mutex(&game->mtx[MTX_GATE], MTX_LOCK, game);
	spr->current_frame += 1;
	safe_mutex(&game->mtx[MTX_GATE], MTX_UNLOCK, game);
	if (spr->current_frame == spr->frame_count)
	{
		spr->current_frame = IMG_BASE;
		(*spr->frame[IMG_BASE]).enabled = true;
		return ;
	}
	(*spr->frame[spr->current_frame]).enabled = true;
	wait_frame(game, FRAME_LIMIT);
}
