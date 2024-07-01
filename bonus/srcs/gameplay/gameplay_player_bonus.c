/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:08:54 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 15:04:02 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	init_player_info(t_cubed *game)
{
	set_player_value(&game->plr->health, 100, game);
	game->plr->img[H] = mlx_put_string(game->mlx,
			get_player_str(&game->plr->health, game), 20, HUD_MIDDLE);
	safe_resize(game->plr->img[H], 150, 150, game);
	set_player_value(&game->plr->ammo, 10, game);
	game->plr->img[A] = mlx_put_string(game->mlx,
			get_player_str(&game->plr->ammo, game), 1750, HUD_MIDDLE);
	safe_resize(game->plr->img[A], 150, 150, game);
}
