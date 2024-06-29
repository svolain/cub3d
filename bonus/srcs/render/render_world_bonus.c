/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:18:21 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/26 11:31:35 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	*render_sprites(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, game);
		draw_sprites(&cam, game);
		wait_frame(game, FRAME_LIMIT);
	}
	return (NULL);
}

void	*render_floor(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, game);
		draw_floor(&cam, cam.a, game);
		wait_frame(game, FRAME_LIMIT);
	}
	return (NULL);
}

void	*render_walls(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, game);
		draw_walls(&cam, cam.a, game);
		wait_frame(game, FRAME_LIMIT);
	}
	return (NULL);
}
