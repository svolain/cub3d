/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_frm_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:56:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/30 14:56:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	*get_portal_frame(t_sprite *spr, t_cubed *game)
{
	mlx_image_t	*img;

	safe_mutex(&game->mtx[MTX_GATE], MTX_LOCK, game);
	img = spr->frame[spr->current_frame];
	safe_mutex(&game->mtx[MTX_GATE], MTX_UNLOCK, game);
	return (img);
}
