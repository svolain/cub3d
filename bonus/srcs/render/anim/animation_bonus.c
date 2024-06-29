/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:35 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/28 12:01:16 by vsavolai         ###   ########.fr       */
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

void	animate_weapon(t_cubed *game)
{
	if (!get_status(&game->wpn->active, &game->mtx[MTX_WPN], game))
		return ;
	game->wpn->timer = game->mlx->delta_time;
	if (game->wpn->timer < game->wpn->delay)
		return ;
	(*game->weapon[game->wpn->current_frame]).enabled = false;
	game->wpn->current_frame += 1;
	game->wpn->timer = 0;
	if (game->wpn->current_frame == game->wpn->frame_count)
	{
		set_status(&game->wpn->active, false, &game->mtx[MTX_WPN], game);
		game->wpn->current_frame = IMG_GO;
		(*game->weapon[IMG_GO]).enabled = true;
		return ;
	}
	(*game->weapon[game->wpn->current_frame]).enabled = true;
	wait_frame(game, FRAME_LIMIT / 10.0f);
}

void	draw_weapon(t_cubed *game)
{
	int	i;

	i = IMG_G15;
	while (i > IMG_G1)
	{
		safe_draw(game->weapon[i], 0, 0, game);
		(*game->weapon[i]).enabled = false;
		i--;
	}
	safe_draw(game->weapon[IMG_GO], 0, 0, game);
}

void	init_weapon(t_cubed *game)
{
	game->wpn = safe_calloc(sizeof(t_anim), game);
	game->wpn->active = 0;
	game->wpn->move_wpn = 0;
	game->wpn->delay = 0.001f;
	game->wpn->frame_count = FRAMES_WEAPON;
	game->wpn->current_frame = IMG_GO;
}

void	animate_weapon_move(t_cubed	*game)
{
	static int	i;
	static int	dir;

	if (!get_status(&game->wpn->move_wpn, &game->mtx[MTX_WPN], game))
		return ;
	if (i == 0 && dir == 0)
		dir = 1;
	if (i > 10)
		dir = -1;
	else if (i < -10)
		dir = 1;
	i += dir;
	game->weapon[IMG_GO]->instances->x += 10 * dir;
	if (i == 2 || i == -4 || i == 6 || i == -8)
		game->weapon[IMG_GO]->instances->y += 10;
	else if (i == -2 || i == 4 || i == -6 || i == 8)
		game->weapon[IMG_GO]->instances->y -= 10;
	set_status(&game->wpn->move_wpn, false, &game->mtx[MTX_WPN], game);
}
