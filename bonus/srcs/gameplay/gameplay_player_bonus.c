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
	set_player_value(&game->plr->ammo, 10, game);

	char	*s1 = get_player_str(&game->plr->health, game);
	char	*s2 = get_player_str(&game->plr->ammo, game);

	mlx_put_string(game->mlx, s1, 20, HUD_MIDDLE);
	mlx_put_string(game->mlx, s2, 1750, HUD_MIDDLE);

	//safe_resize(a, 150, 150, game);
	//safe_resize(b, 150, 150, game);

	mlx_put_string(game->mlx, "HEALTH", 200, HUD_MIDDLE);
	//safe_resize(c, 100, 100, game);
	//safe_resize(game->plr->img[H], 20, 20, game);
	
	//game->plr->img[A] = mlx_put_string(game->mlx,
	//		get_player_str(&game->plr->ammo, game), 1750, HUD_MIDDLE);
	//safe_resize(game->plr->img[A], 20, 20, game);
}
