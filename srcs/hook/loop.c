/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:59:41 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/31 19:59:45 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

/* static void	wait_frame(t_cubed *game) */
/* { */
/* 	static double	frame = 0; */
/**/
/* 	while (frame < game->frame) */
/* 		frame += game->mlx->delta_time; */
/* 	game->frame += FPS; */
/* } */

void	draw_scene(void *param)
{
	t_cubed	*game;

	game = param;
	/* wait_frame(game); */
	draw_minimap(game);
	draw_walls(game);
}
