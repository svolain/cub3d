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

void	set_sprite_frame(t_sprite *spr, t_mtx *mutex, t_cubed *game)
{
	safe_mutex(mutex, MTX_LOCK, game);
	spr->current_frame += 1;
	if (spr->current_frame == spr->frame_count)
		spr->current_frame = IMG_BASE;
	safe_mutex(mutex, MTX_UNLOCK, game);
}

void	*get_sprite_frame(t_sprite *spr, t_mtx *mutex, t_cubed *game)
{
	mlx_image_t	*img;

	safe_mutex(mutex, MTX_LOCK, game);
	img = spr->frame[spr->current_frame];
	safe_mutex(mutex, MTX_UNLOCK, game);
	return (img);
}
