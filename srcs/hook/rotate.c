/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:17:29 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 15:43:09 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	hook_mouse(void *param)
{
	t_cubed	*game;
	int32_t	mouse[2];

	game = param;
	mlx_get_mouse_pos(game->mlx, &mouse[X], &mouse[Y]);
	if (mouse[X] < game->mouse[X])
		rotate_camera(game, ROTATE_LEFT);
	else if (mouse[X] > game->mouse[X])
		rotate_camera(game, ROTATE_RIGHT);
	game->mouse[X] = mouse[X];
}

void	fix_fisheye(t_vector *ray, float angle)
{
	ft_rotate(&angle, ray->a, ROTATE_LEFT);
	ray->d *= cos(angle);
}

void	rotate_camera(t_cubed *game, t_action action)
{
	t_camera	cam;

	get_camera(&cam, &game->mtx[MTX_CAM], game);
	if (action == ROTATE_LEFT)
		ft_rotate(&cam.a, STEP_ANGLE, ROTATE_LEFT);
	else
		ft_rotate(&cam.a, STEP_ANGLE, ROTATE_RIGHT);
	cam.dx = cos(cam.a) * STEP_MOVEMENT;
	cam.dy = sin(cam.a) * STEP_MOVEMENT;
	set_camera(&cam, &game->mtx[MTX_CAM], game);
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

/* int		i; */
/* if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT)) */
/* { */
/* 	i = IMG_G1; */
/* 	while (++i < IMG_G15 + 2) */
/* 	{ */
/* 		animate_shotgun(game, i); */
/* 	} */
/* } */
