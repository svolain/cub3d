/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:11:52 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 08:21:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	set_status(bool *dst, bool val, t_mtx *mutex, t_cubed *game)
{
	safe_mutex(mutex, MTX_LOCK, game);
	*dst = val;
	safe_mutex(mutex, MTX_UNLOCK, game);
}

bool	get_status(bool *val, t_mtx *mutex, t_cubed *game)
{
	bool	ret;

	safe_mutex(mutex, MTX_LOCK, game);
	ret = *val;
	safe_mutex(mutex, MTX_UNLOCK, game);
	return (ret);
}

bool	game_over(t_cubed *game)
{
	return (get_status(&game->status[STAT_DONE], &game->mtx[MTX_DONE], game));
}

void	set_game_over(t_cubed *game)
{
	set_status(&game->status[STAT_DONE], true, &game->mtx[MTX_DONE], game);
}
