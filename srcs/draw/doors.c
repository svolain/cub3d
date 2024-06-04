/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 06:47:04 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/04 19:41:30 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	animate_door(int column, t_vector *ray, t_cubed *game)
{
	int	height;

	calculate_ray(ray, game);
	fix_fisheye(ray, game);
	height = CELLSIZE * SCREEN_HEIGHT / ray->d;
	calculate_draw(&height, ray, game);
	draw_segment(column, height, ray, game);
}

static int	find_rightedge(t_vector *right, t_cubed *game, t_action action)
{
	float	angle;
	int		column;
	int		map[2];

	column = SCREEN_WIDTH - 1;
	angle = game->cam->a;
	ft_rotate(&angle, FOV / 2, ROTATE_RIGHT);
	while (column >= 0)
	{
		right->a = angle;
		calculate_ray(right, game);
		get_position(map, right->x, right->y);
		if (game->map->matrix[map[Y]][map[X]] == MAP_CLOSED)
			break ;
		ft_rotate(&angle, STEP_WINDOW, ROTATE_LEFT);
		column--;
	}
	if (action == DOOR_OPEN)
		game->map->matrix[map[Y]][map[X]] = MAP_OPENED;
	else if (action == DOOR_CLOSE)
		game->map->matrix[map[Y]][map[X]] = MAP_CLOSED;
	return (column);
}

static int	find_leftedge(t_vector *left, t_cubed *game)
{
	float	angle;
	int		column;
	int		map[2];

	column = 0;
	angle = game->cam->a;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (column < SCREEN_WIDTH)
	{
		left->a = angle;
		calculate_ray(left, game);
		get_position(map, left->x, left->y);
		if (game->map->matrix[map[Y]][map[X]] == MAP_CLOSED)
			break ;
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		column++;
	}
	return (column);
}

void	close_door(t_cubed *game)
{
	t_vector	left;
	t_vector	right;
	int			end[2];
	int			mid[2];

	end[A] = find_leftedge(&left, game);
	end[B] = find_rightedge(&right, game, DOOR_CLOSE);
	mid[A] = (end[A] + end[B]) / 2;
	mid[B] = (end[A] + end[B]) / 2;
	game->status[STAT_CLOSE] = true;
	while (end[A] <= mid[A] && end[B] >= mid[B])
	{
		animate_door(mid[A]++, &left, game);
		ft_rotate(&left.a, STEP_WINDOW, ROTATE_RIGHT);
		animate_door(mid[B]--, &right, game);
		ft_rotate(&right.a, STEP_WINDOW, ROTATE_LEFT);
		wait_frame(game, 10000);
	}
	game->status[STAT_CLOSE] = false;
}

void	open_door(t_cubed *game)
{
	t_vector	left;
	t_vector	right;
	int			end[2];
	int			mid[2];

	end[A] = find_leftedge(&left, game);
	end[B] = find_rightedge(&right, game, DOOR_OPEN);
	mid[A] = (end[A] + end[B]) / 2;
	mid[B] = (end[A] + end[B]) / 2;
	game->status[STAT_OPEN] = true;
	left.a = game->cam->a;
	right.a = game->cam->a;
	while (mid[A] >= end[A] && mid[B] <= end[B])
	{
		animate_door(mid[A]--, &left, game);
		ft_rotate(&left.a, STEP_WINDOW, ROTATE_LEFT);
		animate_door(mid[B]++, &right, game);
		ft_rotate(&right.a, STEP_WINDOW, ROTATE_RIGHT);
		wait_frame(game, 10000);
	}
	game->status[STAT_OPEN] = false;
}
