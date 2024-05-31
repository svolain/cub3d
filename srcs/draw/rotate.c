/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:17:29 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/31 15:34:51 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	rotate_camera(t_cubed *game, t_action action)
{
	if (action == ROTATE_LEFT)
		ft_rotate(&game->cam->a, STEP_ANGLE, ROTATE_LEFT);
	else
		ft_rotate(&game->cam->a, STEP_ANGLE, ROTATE_RIGHT);
	game->cam->dx = cos(game->cam->a) * STEP_MOVEMENT;
	game->cam->dy = sin(game->cam->a) * STEP_MOVEMENT;
}

void	ft_rotate(float *target, float angle, t_action action)
{
	if (action == ROTATE_LEFT)
	{
		*target -= angle;
		if (*target < 0)
			*target += 2 * PI;
	}
	else if (action == ROTATE_RIGHT)
	{
		*target += angle;
		if (*target > 2 * PI)
			*target -= 2 * PI;
	}
}

float	ft_degtorad(float degree)
{
	return (degree * PI / 180);
}
