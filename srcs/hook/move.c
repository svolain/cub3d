/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:30:49 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/07 10:12:26 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

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
/* 	int xa = (buffer[X] + game->cam->x) / CELLSIZE; */
/* 	int ya = (buffer[Y] + game->cam->y) / CELLSIZE; */
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

/* void	check_collision(float x, float y, t_cubed *game) */
/* { */
/**/
/* } */

void	move_camera(t_cubed *game, t_action action)
{
	if (action == MOVE_UP)
	{
		game->cam->x += game->cam->dx;
		game->cam->y += game->cam->dy;
	}
	else if (action == MOVE_DOWN)
	{
		game->cam->x -= game->cam->dx;
		game->cam->y -= game->cam->dy;
	}
	else if (action == MOVE_LEFT)
	{
		game->cam->x -= -game->cam->dy;
		game->cam->y -= game->cam->dx;
	}
	else
	{
		game->cam->x += -game->cam->dy;
		game->cam->y += game->cam->dx;
	}
	animate_minimap(game);
}
