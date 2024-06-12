/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:30:49 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 15:42:16 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static bool	ft_is_collision(t_camera *cam, int prev[2], t_cubed *game)
{
	int	map[2];

	(void)prev;
	get_map_position(map, cam->x, cam->y);
	if (!ft_strchr(CHARSET_MOVEABLE,
		get_map_element(map[X], map[Y], game)))
		return (true);
	return (false);
}

static void update_position(t_camera *cam, float delta_x, float delta_y)
{
	cam->x += delta_x;
	cam->y += delta_y;
}

void	move_camera(t_cubed *game, t_action action)
{
	t_camera	cam;
	int			prev[2];

	get_camera(&cam, &game->mtx[MTX_CAM], game);
	get_map_position(prev, cam.x, cam.y);
	if (action == MOVE_UP)
		update_position(&cam, cam.dx, cam.dy);
	else if (action == MOVE_DOWN)
		update_position(&cam, -cam.dx, -cam.dy);
	else if (action == MOVE_LEFT)
		update_position(&cam, cam.dy, -cam.dx);
	else if (action == MOVE_RIGHT)
		update_position(&cam, -cam.dy, cam.dx);
	if (!ft_is_collision(&cam, prev, game))
		set_camera(&cam, &game->mtx[MTX_CAM], game);
}

/* static void	check_collision(int *dest, int *player, int *new, t_cubed *game) */
/* { */
/* 	if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[player[Y]][new[X]])) */
/* 		game->cam->x = dest[X]; */
/* 	if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[new[Y]][player[X]])) */
/* 		game->cam->y = dest[Y]; */
/* } */

/* static void	update_position(int *dest, t_action action, t_cubed *game) */
/* { */
/* 	int	bump[2]; */
/* 	int	player[2]; */
/* 	int	new[2]; */
/**/
/* 	get_map_position(player, game->cam->x, game->cam->y); */
/* 	set_buffer(bump, BUMP_BUFFER, game); */
/* 	if (action == MOVE_UP) */
/* 	{ */
/* 		new[X] = (bump[X] + game->cam->x) / CELLSIZE; */
/* 		new[Y] = (bump[Y] + game->cam->y) / CELLSIZE; */
/* 	} */
/* 	else if (action == MOVE_DOWN) */
/* 	{ */
/* 		new[X] = (game->cam->x - bump[X]) / CELLSIZE; */
/* 		new[Y] = (game->cam->y - bump[Y]) / CELLSIZE; */
/* 	} */
/* 	else if ((action == MOVE_LEFT && (game->cam->a < NORTH || (game->cam->a > WEST && game->cam->a < SOUTH))) */
/* 		|| (action == MOVE_RIGHT && (game->cam->a > SOUTH || (game->cam->a > NORTH && game->cam->a < WEST)))) */
/* 	{ */
/* 		new[X] = (bump[X] + game->cam->x) / CELLSIZE; */
/* 		new[Y] = (game->cam->y - bump[Y]) / CELLSIZE; */
/* 	} */
/* 	else */
/* 	{ */
/* 		new[X] = (game->cam->x - bump[X]) / CELLSIZE; */
/* 		new[Y] = (bump[Y] + game->cam->y) / CELLSIZE; */
/* 	} */
/* 	check_collision(dest, player, new, game); */
/* } */

/* static void	update_position(int *dest, t_action action, t_cubed *game) */
/* { */
/* 	int	buffer[2]; */
/* 	int	player[2]; */
/**/
/* 	get_map_position(player, game->cam->x, game->cam->y); */
/* 	set_buffer(buffer, BUMP_BUFFER, game); */
/* 	int xa = (game->cam->x + buffer[X]) / CELLSIZE; */
/* 	int ya = (game->cam->y + buffer[Y]) / CELLSIZE; */
/* 	int xs = (game->cam->x - buffer[X]) / CELLSIZE; */
/* 	int ys = (game->cam->y - buffer[Y]) / CELLSIZE; */
/**/
/* 	if (action == MOVE_UP) */
/* 	{ */
/* 		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[player[Y]][xa])) */
/* 			game->cam->x = dest[X]; */
/* 		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ya][player[X]])) */
/* 			game->cam->y = dest[Y]; */
/* 	} */
/* 	else if (action == MOVE_DOWN) */
/* 	{ */
/* 		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[player[Y]][xs])) */
/* 			game->cam->x = dest[X]; */
/* 		if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ys][player[X]])) */
/* 			game->cam->y = dest[Y]; */
/* 	} */
/* 	else if (action == MOVE_LEFT) */
/* 	{ */
/* 		if (game->cam->a < NORTH || (game->cam->a > WEST && game->cam->a < SOUTH)) */
/* 		{ */
/* 			if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[player[Y]][xa])) */
/* 				game->cam->x = dest[X]; */
/* 			if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ys][player[X]])) */
/* 				game->cam->y = dest[Y]; */
/* 		} */
/* 		else */
/* 		{ */
/* 			if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[player[Y]][xs])) */
/* 				game->cam->x = dest[X]; */
/* 			if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ya][player[X]])) */
/* 				game->cam->y = dest[Y]; */
/* 		} */
/* 	} */
/* 	else */
/* 	{ */
/* 		if (game->cam->a < NORTH || (game->cam->a > WEST && game->cam->a < SOUTH)) */
/* 		{ */
/* 			if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[player[Y]][xs])) */
/* 				game->cam->x = dest[X]; */
/* 			if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ya][player[X]])) */
/* 				game->cam->y = dest[Y]; */
/* 		} */
/* 		else */
/* 		{ */
/* 			if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[player[Y]][xa])) */
/* 				game->cam->x = dest[X]; */
/* 			if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[ys][player[X]])) */
/* 				game->cam->y = dest[Y]; */
/* 		} */
/* 	} */
/* } */

/* void	check_collision(float *prev, t_cubed *game) */
/* { */
/* 	int	buffer[2]; */
/* 	int	player[2]; */
/**/
/* 	set_buffer(buffer, BUMP_BUFFER, game); */
/* 	get_map_position(player, game->cam->x, game->cam->y); */
/* 	if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[player[Y]][xa])) */
/* 		game->cam->x = prev[X]; */
/* 	if (ft_strchr(CHARSET_MOVEABLE, game->map->matrix[player[Y]][xa])) */
/* 		game->cam->y = prev[Y]; */
/* } */
