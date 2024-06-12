/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:11:43 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 14:01:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	set_bool(bool *dst, bool val, t_mtx *mutex, t_cubed *game)
{
	safe_mutex(mutex, MTX_LOCK, game);
	*dst = val;
	safe_mutex(mutex, MTX_UNLOCK, game);
}

bool	get_bool(bool *val, t_mtx *mutex, t_cubed *game)
{
	bool	ret;

	safe_mutex(mutex, MTX_LOCK, game);
	ret = *val;
	safe_mutex(mutex, MTX_UNLOCK, game);
	return (ret);
}

void	set_float(float *dst, float val, t_mtx *mutex, t_cubed *game)
{
	safe_mutex(mutex, MTX_LOCK, game);
	*dst = val;
	safe_mutex(mutex, MTX_UNLOCK, game);
}

float	get_float(float *val, t_mtx *mutex, t_cubed *game)
{
	float	ret;

	safe_mutex(mutex, MTX_LOCK, game);
	ret = *val;
	safe_mutex(mutex, MTX_UNLOCK, game);
	return (ret);
}

void	set_camera(t_camera *cam, t_mtx *mutex, t_cubed *game)
{
	safe_mutex(mutex, MTX_LOCK, game);
	game->cam->a = cam->a;
	game->cam->x = cam->x;
	game->cam->y = cam->y;
	game->cam->dx = cam->dx;
	game->cam->dy = cam->dy;
	safe_mutex(mutex, MTX_UNLOCK, game);
}

void	get_camera(t_camera *cam, t_mtx *mutex, t_cubed *game)
{
	safe_mutex(mutex, MTX_LOCK, game);
	cam->a = game->cam->a;
	cam->x = game->cam->x;
	cam->y = game->cam->y;
	cam->dx = game->cam->dx;
	cam->dy = game->cam->dy;
	safe_mutex(mutex, MTX_UNLOCK, game);
}
