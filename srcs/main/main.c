/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:32:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/12 20:36:57 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

float	py = 4 * CELLSIZE;
float	px = 4 * CELLSIZE;
float	pa = NORTH;

mlx_t			*mlx;
mlx_image_t 	*player;
mlx_image_t 	*wall;
mlx_image_t		*img;

char *map[] = { "11111111\n",
				"10100001\n",
				"10100001\n",
				"10100001\n",
				"10000001\n",
				"10000101\n",
				"10000001\n",
				"11111111" };

void	find_collosion_point(t_vector *vec, float offset_x, float offset_y)
{
	float	map_x;
	float	map_y;
	int		i;

	i = 0;
	while (i < 8) // TODO replace iterative loop with infinite since walls are closed
	{
		// TODO need to add limit checks so coordinates won't overflow
		// should be calculated from player x/y distance from map edge using CELLSIZE
		map_x = (int)vec->y / CELLSIZE;
		map_y = (int)vec->x / CELLSIZE;
		if (map[map_y][map_x] == '1')
			break ;
		else
		{
			vec->x += offset_x;
			vec->y += offset_y;
		}
		i++;
	}
	vec->x = map_x;
	vec->y = map_y;
}

void	horizontal_collosion(t_vector *vec)
{
	float	offset_x;
	float	offset_y;

	vec->angle = pa; //TODO need to check if vector angle is really needed
	if (vec->angle < WEST)
	{
		vec->y = ((py / CELLSIZE) * CELLSIZE) + (Y.line - py);
		vec->x = (py - vec->y) / -tan(pa) + px;
		offset_y = CELLSIZE;
		offset_x = offset_y * tan(pa);
	}
	else if (vec->angle > WEST)
	{
		vec->y = ((py / CELLSIZE) * CELLSIZE) - (Y.line - py);
		vec->x = (py - vec->y) / -tan(pa) + px;
		offset_y = -CELLSIZE;
		offset_x = offset_y * tan(pa);
	}
	find_collosion_point(vec, offset_x, offset_y);
}

void	vertical_collosion(t_vector *vec)
{
	float	offset_x;
	float	offset_y;

	vec->angle = pa; //TODO need to check if vector angle is really needed
	if (vec->angle < NORTH || vec->angle > SOUTH)
	{
		vec->x = ((px / CELLSIZE) * CELLSIZE) + (X.line - px);
		vec->y = (px - vec->x) / -tan(pa) + py;
		offset_x = CELLSIZE;
		offset_y = offset_x * tan(pa);
	}
	else if (vec->angle > NORTH || vec->angle < SOUTH)
	{
		vec->x = ((px / CELLSIZE) * CELLSIZE) - (X.line - px);
		vec->y = (px - vec->x) / -tan(pa) + py;
		offset_x = -CELLSIZE;
		offset_y = offset_x * tan(pa);
	}
	find_collosion_point(vec, offset_x, offset_y);
}

void	rotate_player_left()
{
	t_vector	horizontal;
	t_vector	vertical;

	pa -= STEP_ANGLE;
	if (pa < 0)
		pa += 2 * PI;
	horizontal_collosion(&horizontal);
	vertical_collosion(&vertical);
	// TODO need to calculate which collosion happened first
	// TODO need to create test drawing function
}

void	rotate_player_right()
{
	t_vector	horizontal;
	t_vector	vertical;

	pa += STEP_ANGLE;
	if (pa > 2 * PI)
		pa -= 2 * PI;
	horizontal_collosion(&horizontal);
	vertical_collosion(&vertical);
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
			player->instances[0].y -= STEP_MOVE;
			py -= STEP_MOVE;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_S))
		{
			player->instances[0].y += STEP_MOVE;
			py += STEP_MOVE;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_A))
		{
			player->instances[0].x -= STEP_MOVE;
			px -= STEP_MOVE;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_D))
		{
			player->instances[0].x += STEP_MOVE;
			px += STEP_MOVE;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
			rotate_player_right();
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			rotate_player_left();
	}
}

int	main(void)
{
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
