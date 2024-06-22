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

#include <cubed_bonus.h>

void	wait_frame(t_cubed *game, float limit)
{
	double	frame;

	frame = 0;
	while (frame < limit)
		frame += game->mlx->delta_time;
}

void	animate_weapon(t_cubed *game)
{
	if (!get_status(&game->wpn->active, &game->mtx[MTX_ANIM], game))
		return ;
	game->wpn->timer = game->mlx->delta_time;
	if (game->wpn->timer < game->wpn->delay)
		return ;
	(*game->anim[game->wpn->current_frame]).enabled = false;
	game->wpn->current_frame += 1;
	game->wpn->timer = 0;
	if (game->wpn->current_frame == game->wpn->frame_count)
	{
		set_status(&game->wpn->active, false, &game->mtx[MTX_ANIM], game);
		game->wpn->current_frame = IMG_GO;
		(*game->anim[IMG_GO]).enabled = true;
		return ;
	}
	(*game->anim[game->wpn->current_frame]).enabled = true;
	wait_frame(game, 200);
}

void	draw_weapon(t_cubed *game)
{
	int	i;

	i = IMG_G15;
	while (i > IMG_G1)
	{
		safe_draw(game->anim[i], 0, 0, game);
		(*game->anim[i]).enabled = false;
		i--;
	}
	safe_draw(game->anim[IMG_GO], 0, 0, game);
}

void	init_animation(t_cubed *game)
{
	game->wpn = safe_calloc(sizeof(t_anim), game);
	game->wpn->active = 0;
	game->wpn->delay = 0.02f;
	game->wpn->frame_count = GAME_ANIMS;
	game->wpn->current_frame = IMG_GO;
}
