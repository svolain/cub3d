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

#include <cubed.h>

bool	game_over(t_cubed *game)
{
	return (get_bool(&game->stt[STT_DONE], &game->mtx[MTX_DONE], game));
}

void	set_finished(t_cubed *game)
{
	set_bool(&game->stt[STT_DONE], true, &game->mtx[MTX_DONE], game);
}
