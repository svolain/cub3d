/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:18:21 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/14 16:18:24 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	*render_fov(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, game);
		draw_fov(&cam, cam.a, game);
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
	}
	return (NULL);
}
