/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 06:47:11 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/03 12:10:09 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	hook_close(void *param)
{
	t_cubed	*game;

	game = param;
	free_exit(game, NOERROR);
}

static bool	active_door(t_cubed *game)
{
	int	buffer[2];
	int	player[2];
	int	map[2];

	get_position(player, game->cam->x, game->cam->y);
	set_buffer(buffer, BUMP_BUFFER, game);
	map[X] = (game->cam->x + game->cam->dx + buffer[X]) / CELLSIZE;
	map[Y] = (game->cam->y + game->cam->dy + buffer[Y]) / CELLSIZE;
	if (game->map->matrix[player[Y]][player[X]] != MAP_OPENED)
	{
		if (game->map->matrix[map[Y]][map[X]] == MAP_CLOSED)
		{
			open_door(game);
			return (true);
		}
		else if (game->map->matrix[map[Y]][map[X]] == MAP_OPENED)
		{
			game->map->matrix[map[Y]][map[X]] = MAP_CLOSED;
			return (true);
		}
	}
	return (false);
}

void	hook_actions(mlx_key_data_t keydata, void *param)
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
