/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:30:49 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/27 18:16:51 by vsavolai         ###   ########.fr       */
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
	if (!ft_in_elements(cam->x, cam->y, CHARSET_MOVEABLE, game))
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
	set_status(&game->sprite[SPRT_WPN]->status[MOVE_WPN],
		true, &game->mtx[MTX_WPN], game);
}
