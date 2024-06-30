/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:35 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/30 11:49:37 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	weapon_shoot(t_sprite *spr, t_cubed *game)
{
	if (!get_status(&spr->status[SHOOT_WPN],
			&game->mtx[MTX_WPN], game))
		return ;
	(*spr->frame[spr->current_frame]).enabled = false;
	spr->current_frame += 1;
	if (spr->current_frame == spr->frame_count)
	{
		set_status(&spr->status[SHOOT_WPN],
			false, &game->mtx[MTX_WPN], game);
		spr->current_frame = IMG_BASE;
		(*spr->frame[IMG_BASE]).enabled = true;
		return ;
	}
	(*spr->frame[spr->current_frame]).enabled = true;
	wait_frame(game, FRAME_LIMIT);
}

void	weapon_move(t_sprite *spr, t_cubed	*game)
{
	static int	step_limit = 15;
	static int	pixels = 8;
	static int	i = 0;

	if (!get_status(&spr->status[MOVE_WPN],
			&game->mtx[MTX_WPN], game))
		return ;
	spr->frame[IMG_BASE]->instances->x += pixels;
	if (i < step_limit / 2)
		spr->frame[IMG_BASE]->instances->y += pixels / 2;
	else
		spr->frame[IMG_BASE]->instances->y += -pixels / 2;
	if (i == step_limit)
	{
		pixels = -pixels;
		i = 0;
	}
	set_status(&spr->status[MOVE_WPN],
		false, &game->mtx[MTX_WPN], game);
	i++;
}

void	draw_weapon_frames(t_sprite *spr, t_cubed *game)
{
	int	offset[2];
	int	i;

	i = IMG_W15;
	offset[X] = SCREEN_WIDTH - spr->frame[IMG_BASE]->width;
	offset[Y] = SCREEN_HEIGHT - spr->frame[IMG_BASE]->height;
	while (i > IMG_W1)
	{
		safe_draw(spr->frame[i], offset[X], offset[Y], game);
		(*spr->frame[i]).enabled = false;
		i--;
	}
	safe_draw(spr->frame[IMG_BASE], offset[X], offset[Y], game);
}
