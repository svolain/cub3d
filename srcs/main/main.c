/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:32:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/14 09:18:53 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

mlx_t			*mlx;
mlx_image_t 	*player;
mlx_image_t 	*wall;
mlx_image_t		*img;

void	rotate_player_left()
{
	pa -= STEP_ANGLE;
	if (pa < 0)
		pa += 2 * PI;
	calculate_rays();
}

void	rotate_player_right()
{
	pa += STEP_ANGLE;
	if (pa > 2 * PI)
		pa -= 2 * PI;
	calculate_rays();
}

void	move_keyhook(mlx_key_data_t keydata, void *param)
{
	if (!param)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
	if (player->instances[0].enabled == true)
	{
		if (mlx_is_key_down(mlx, MLX_KEY_W))
		{
			player->instances[0].y -= STEP_MOVEMENT;
			py -= STEP_MOVEMENT;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_S))
		{
			player->instances[0].y += STEP_MOVEMENT;
			py += STEP_MOVEMENT;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_A))
		{
			player->instances[0].x -= STEP_MOVEMENT;
			px -= STEP_MOVEMENT;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_D))
		{
			player->instances[0].x += STEP_MOVEMENT;
			px += STEP_MOVEMENT;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
			rotate_player_right();
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			rotate_player_left();
	}
}

int	main(int argc, char **argv)
{
	t_cubed	*game;

	if (argc != 2)
		error_exit(ERR_ARGC, MSG_ARGC, NULL);
	init_game(&game, argv[1]);








	int i = 0;
	int j = 0;

	mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", false);
	player = mlx_new_image(mlx, 16, 16);
	ft_memset(player->pixels, 200, player->width * player->height * BPP);
	wall = mlx_new_image(mlx, CELLSIZE - 2, CELLSIZE - 2);
	ft_memset(wall->pixels, 255, wall->width * wall->height * BPP);
	while (i < 8)
	{
		j = 0;
		while(j < 8)
		{
			if(map[i][j] == '1')
				mlx_image_to_window(mlx, wall, j * CELLSIZE, i * CELLSIZE);
			j++;
		}
		i++;
	}
	mlx_image_to_window(mlx, player, px, py);
	mlx_key_hook(mlx, &move_keyhook, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);

	return (0);
}
