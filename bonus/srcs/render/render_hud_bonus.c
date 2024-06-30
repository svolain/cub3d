/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:18:21 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/28 13:53:58 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	*render_fov(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, game);
		draw_fov(&cam, cam.a, game);
		wait_frame(game, FRAME_LIMIT);
	}
	return (NULL);
}

void	*render_minimap(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, game);
		draw_minimap(cam.x, cam.y, game);
		wait_frame(game, FRAME_LIMIT);
	}
	return (NULL);
}

void	*render_hud(void *param)
{
	t_cubed		*game;

	game = param;
	while (!game_over(game))
	{
		draw_hud(game);
		wait_frame(game, FRAME_LIMIT);
	}
	return (NULL);
}
