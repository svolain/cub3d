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

void	*render_minimap(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, game);
		draw_minimap(&cam, cam.x, cam.y, game);
	}
	return (NULL);
}

void	*render_background(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, game);
		draw_background(&cam, cam.a, game);
	}
	return (NULL);
}

void	*render_foreground(void *param)
{
	t_cubed		*game;
	t_camera	cam;

	game = param;
	while (!game_over(game))
	{
		get_camera(&cam, game);
		draw_foreground(&cam, cam.a, game);
	}
	return (NULL);
}
