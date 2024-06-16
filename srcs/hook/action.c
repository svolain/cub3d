/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 06:47:11 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/13 08:44:01 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	hook_close(void *param)
{
	t_cubed	*game;

	game = param;
	free_exit(game, NOERROR);
}

static void	set_map_buffer(int buffer[2], int size, t_camera *cam)
{
	buffer[X] = size;
	buffer[Y] = size;
	if (cam->dx < 0)
		buffer[X] = -buffer[X];
	if (cam->dy < 0)
		buffer[Y] = -buffer[Y];
}

static void	active_door(t_cubed *game)
{
	t_camera	cam;
	int			map[2];
	int			player[2];
	int			buffer[2];

	get_camera(&cam, game);
	set_map_buffer(buffer, BUMP_BUFFER, &cam);
	get_map_position(player, cam.x, cam.y);
	get_map_position(map, cam.x + buffer[X], cam.y + buffer[Y]);
	if (get_map_element(player[X], player[Y], game) != MAP_OPENED)
	{
		if (get_map_element(map[X], map[Y], game) == MAP_CLOSED)
			set_map_element(map[X], map[Y], MAP_OPENED, game);
		else if (get_map_element(map[X], map[Y], game) == MAP_OPENED)
			set_map_element(map[X], map[Y], MAP_CLOSED, game);
	}
}

void	hook_action(mlx_key_data_t keydata, void *param)
{
	t_cubed		*game;

	game = param;
	if (keydata.action == MLX_PRESS)
	{
		if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)
			|| mlx_is_key_down(game->mlx, MLX_KEY_Q))
			free_exit(game, NOERROR);
		if (mlx_is_key_down(game->mlx, MLX_KEY_E))
			active_door(game);
	}
}

void	hook_movement(void *param)
{
	t_cubed	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_camera(game, MOVE_UP);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_camera(game, MOVE_DOWN);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_camera(game, MOVE_LEFT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_camera(game, MOVE_RIGHT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_camera(game, ROTATE_RIGHT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_camera(game, ROTATE_LEFT);
}
