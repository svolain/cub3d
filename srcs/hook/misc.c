/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:21:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/05 21:53:26 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	hook_close(void *param)
{
	t_cubed	*game;

	game = param;
	free_exit(game, NOERROR);
}

void	set_buffer(int *buffer, int size, t_cubed *game)
{
	buffer[X] = size;
	buffer[Y] = size;
	if (game->cam->dx < 0)
		buffer[X] = -buffer[X];
	if (game->cam->dy < 0)
		buffer[Y] = -buffer[Y];
}

void	get_map_position(int *target, int x, int y)
{
	target[X] = x / CELLSIZE;
	target[Y] = y / CELLSIZE;
}
