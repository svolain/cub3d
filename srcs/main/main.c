/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:32:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/10 16:16:29 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

float				pos_y = 400;
float				pos_x = 400;
float				pdy;
float				pdx;
float				pa;

mlx_t			*mlx;
mlx_image_t 	*player;

void	move_keyhook(mlx_key_data_t keydata, void *param)
{
	char **map;

	map = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
	if (player->instances[0].enabled == true)
	{
		if (mlx_is_key_down(mlx, MLX_KEY_W))
			player->instances[0].y -= 10;
		if (mlx_is_key_down(mlx, MLX_KEY_S))
			player->instances[0].y += 10;
		if (mlx_is_key_down(mlx, MLX_KEY_A))
			player->instances[0].x -= 10;
		if (mlx_is_key_down(mlx, MLX_KEY_D))
			player->instances[0].x += 10;	
	}
}

int	main(void)
{
	mlx_image_t 	*wall;
	mlx_texture_t	*te_player;
	mlx_texture_t	*te_wall;

	char *map[] = { "11111111\n",
					"10100001\n", 
					"10100001\n",
					"10100001\n", 
					"10000001\n", 
					"10000001\n", 
					"10000001\n", 
					"11111111"};
	mlx = mlx_init(800, 800, "cub3d", false);
	if (!mlx)
	{
		printf("mlx init fail");
		exit(1);
	}
	te_player = mlx_load_png("../textures/player.png");
	te_wall = mlx_load_png("../textures/wall.png");
	if (!te_player || !te_wall)
	{
		printf("load png fail");
		exit(1);
	}
	player = mlx_texture_to_image(mlx, te_player);
	wall = mlx_texture_to_image(mlx, te_wall);
	if (!player || !wall)
	{
		printf("new img fail");
		exit(1);
	}
	int i = 0;
	int j;
	while(i < 8)
	{
		j = 0;
		while(j < 8)
		{
			if(map[i][j] == '1')
				mlx_image_to_window(mlx, wall, j * 100, i * 100);
			j++;
		}
		i++;
	}
	if (mlx_image_to_window(mlx, player, pos_x, pos_y) < 0)
	{
		printf("new img fail");
		exit(1);
	}
	mlx_key_hook(mlx, &move_keyhook, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
