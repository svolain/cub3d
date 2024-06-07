/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:59:41 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/05 17:06:38 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

/*static bool	frame_elapsed(t_cubed *game)
{
 	static double	frame = 0;

 	frame += game->mlx->delta_time;
 	if (frame < FPS / 1000)
 		return (false);
 	frame -= FPS / 1000;
	return (true);
 }*/

void	draw_scene(void *param)
{
	t_cubed	*game;
	
	game = param;
	if (game->status[STAT_OPEN])
		open_door(game);
	else if (game->status[STAT_CLOSE])
		close_door(game);
	else
	{
		//if (!frame_elapsed(game))
		// 	return ;
		draw_minimap(game);
		draw_walls(game);
	}
}
