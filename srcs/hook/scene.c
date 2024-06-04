/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:59:41 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/03 15:39:39 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

/* static bool	frame_elapsed(t_cubed *game) */
/* { */
/*  	static double	frame = 0; */
/**/
/*  	frame += game->mlx->delta_time; */
/*  	if (frame < FPS / 1000) */
/*  		return (false); */
/*  	frame -= FPS / 1000; */
/* 	return (true); */
/*  } */

void	draw_scene(void *param)
{
	t_cubed		*game;
	
	game = param;
	if (!game->anims[ANIM_OPEN])
	{
		draw_minimap(game);
		draw_walls(game);
		/* printf("Waiting door animation\n"); */
		/* return ; */
	}
	/* else if (game->anims[0] == true) */
	/* 	open_door(game); */
	/* if (!frame_elapsed(game)) */
	/*  	return ; */
}
