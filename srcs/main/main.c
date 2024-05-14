/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:32:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/12 20:36:57 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

float	py = 4 * CELLSIZE;
float	px = 4 * CELLSIZE;
float	pa = NORTH - DEGREE;

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

void	find_collosion_point(t_vector *vec, float *offset)
{
	int	map_x;
	int	map_y;

	while (true)
	{
		map_x = vec->x / CELLSIZE;
		map_y = vec->y / CELLSIZE;
		if (map_x < 0 || map_x >= 8 // TODO: replace with map width
			|| map_y < 0 || map_y >= 8 // TODO: replace with map height
			|| map[map_y][map_x] != FLOOR)
			break ;
		vec->x += offset[X];
		vec->y += offset[Y];
	}
}

void	horizontal_collosion(t_vector *vec)
{
	float	offset[2];
	float	atan;

	vec->angle = pa;
	atan = 1 / -tan(vec->angle);
	if (vec->angle > WEST)
	{
		vec->y = ((py / CELLSIZE) * CELLSIZE - 0.00001f);
		offset[Y] = -CELLSIZE;
	}
	else
	{
		vec->y = ((py / CELLSIZE) * CELLSIZE) + CELLSIZE;
		offset[Y] = CELLSIZE;
	}
	vec->x = (py - vec->y) * atan + px;
	offset[X] = -offset[Y] * atan;
	find_collosion_point(vec, offset);
}

void	vertical_collosion(t_vector *vec)
{
	float	offset[2];
	float	ntan;

	vec->angle = pa;
	ntan = -tan(vec->angle);
	if (vec->angle > NORTH && vec->angle < SOUTH)
	{
		vec->x = ((px / CELLSIZE) * CELLSIZE) - 0.00001f;
		offset[X] = -CELLSIZE;
	}
	else
	{
		vec->x = ((px / CELLSIZE) * CELLSIZE) + CELLSIZE;
		offset[X] = CELLSIZE;
	}
	vec->y = (px - vec->x) * ntan + py;
	offset[Y] = -offset[X] * ntan;
	find_collosion_point(vec, offset);
}

/* void	calculate_rays() */
/* { */
/* 	t_vector	ray; */
/**/
/**/
/* } */

void	rotate_player_left()
{
	t_vector	horizontal;
	t_vector	vertical;

	pa -= STEP_ANGLE;
	if (pa < 0)
		pa += 2 * PI;
	horizontal_collosion(&horizontal);
	vertical_collosion(&vertical);
	img = mlx_new_image(mlx, 8, 8);
	ft_memset(img->pixels, 222, img->width * img->height * BPP);
	mlx_image_to_window(mlx, img, horizontal.x, horizontal.y);
	mlx_image_to_window(mlx, img, vertical.x, vertical.y);
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
	img = mlx_new_image(mlx, 8, 8);
	ft_memset(img->pixels, 222, img->width * img->height * BPP);
	mlx_image_to_window(mlx, img, horizontal.x, horizontal.y);
	mlx_image_to_window(mlx, img, vertical.x, vertical.y);
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
