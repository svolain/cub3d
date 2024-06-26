/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:30:49 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/13 08:36:01 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	hook_close(void *param)
{
	t_cubed	*game;

	game = param;
	free_exit(game, NOERROR);
}

static bool	ft_is_collision(t_camera *cam, t_cubed *game)
{
	int	map[2];

	get_map_position(map, cam->x, cam->y);
	if (!ft_strchr(CHARSET_MOVEABLE,
			get_map_element(map[X], map[Y], game)))
		return (true);
	return (false);
}

static void	update_position(t_camera *cam, float delta_x, float delta_y)
{
	cam->x += delta_x;
	cam->y += delta_y;
}

void	move_camera(t_cubed *game, t_action action)
{
	t_camera	cam;

	get_camera(&cam, game);
	if (action == MOVE_UP)
		update_position(&cam, cam.dx, cam.dy);
	else if (action == MOVE_DOWN)
		update_position(&cam, -cam.dx, -cam.dy);
	else if (action == MOVE_LEFT)
		update_position(&cam, cam.dy, -cam.dx);
	else if (action == MOVE_RIGHT)
		update_position(&cam, -cam.dy, cam.dx);
	if (!ft_is_collision(&cam, game))
		set_camera(&cam, game);
}
