/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:32:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/11 19:04:13 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

float	py = 4 * CELLSIZE;
float	px = 4 * CELLSIZE;
float	pa = PI / 2;

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

void	horizontal_collation(t_vector *vec)
{
	float	offset_x;
	float	offset_y;

	vec->angle = pa;

	vec->y = ((py / CELLSIZE) * CELLSIZE) + (Y.line - py);
	vec->x = (py - vec->y) / -tan(pa) + px;
	offset_y = CELLSIZE;
	offset_x = offset_y * tan(pa);

	vec->y = ((py / CELLSIZE) * CELLSIZE) - (Y.line - py);
	vec->x = (py - vec->y) / -tan(pa) + px;
	offset_y = -CELLSIZE;
	offset_x = offset_y * tan(pa);
}
void	vertical_collation(t_vector *vec)
{
	float	offset_x;
	float	offset_y;

	vec->angle = pa;

	vec->x = ((px / CELLSIZE) * CELLSIZE) + (X.line - px);
	vec->y = (px - vec->x) / -tan(pa) + py;
	offset_x = CELLSIZE;
	offset_y = offset_x * tan(pa);

	vec->x = ((px / CELLSIZE) * CELLSIZE) - (X.line - px);
	vec->y = (px - vec->x) / -tan(pa) + py;
	offset_x = -CELLSIZE;
	offset_y = offset_x * tan(pa);
}

void	rotate_player_left()
{
	t_vector	horizontal;
	t_vector	vertical;

	pa -= STEP_ANGLE;
	if (pa < 0)
		pa += 2 * PI;
	horizontal_collation(&horizontal);
	vertical_collation(&vertical);
	// drawray();
	// img = mlx_new_image(mlx, 8, 8);
	// ft_memset(img->pixels, 255, img->width * img->height * BPP);
	// mlx_image_to_window(mlx, img, px + pdx, py + pdy);
}

void	rotate_player_right()
{
	t_vector	horizontal;
	t_vector	vertical;

	pa += STEP_ANGLE;
	if (pa > 2 * PI)
		pa -= 2 * PI;
	horizontal_collation(&horizontal);
	vertical_collation(&vertical);
	// img = mlx_new_image(mlx, 8, 8);
	// ft_memset(img->pixels, 255, img->width * img->height * BPP);
	// mlx_image_to_window(mlx, img, px + pdx, py + pdy);
}

void	move_keyhook(mlx_key_data_t keydata, void *param)
{
	char **map;

	map = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
	if (player->instances[0].enabled == true)
	{
		if (mlx_is_key_down(mlx, MLX_KEY_W))
		{
			player->instances[0].y -= 8;
			py -= 8;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_S))
		{
			player->instances[0].y += 8;
			py += 8;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_A))
		{
			player->instances[0].x -= 8;
			px -= 8;
		}
		if (mlx_is_key_down(mlx, MLX_KEY_D))
		{
			player->instances[0].x += 8;
			px += 8;
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

// static int get_rgba(int r, int g, int b, int a)
// {
// 	return (r << 24 | g << 16 | b << 8 | a);
// }

// void	drawray()
// {
// 	int		i;
// 	float	atan;
//
// 	int mx, my, dof; // , mp
// 	float rx, ry, ra, xo, yo;
//
// 	i = 0;
// 	ra = pa;
// 	while (i < 1)
// 	{
// 		dof = 0;
// 		atan = -1 / tan(ra);
// 		if (ra > PI) // ray is facing down
// 		{
// 			ry = ((py / CELLSIZE) * CELLSIZE);
// 			rx = (py - ry) * atan + px;
// 			yo = -64;
// 			xo = -yo * atan;
// 		}
// 		else if (ra < PI) // ray is facing up
// 		{
// 			ry = (((int)py >> 6) << 6) + 64;
// 			rx = (py - ry) * atan + px;
// 			yo = 64;
// 			xo = -yo * atan;
// 		}
// 		else if (ra == 0 || ra == PI) // ray is horizontal
// 			return ;
// 		// {
// 		// 	rx = px;
// 		// 	ry = py;
// 		// 	dof = 8;
// 		// 	xo = 0;
// 		// 	yo = 0;
// 		// }
// 		while (dof < 8)
// 		{
// 			mx = (int)rx >> 6; // >> 6 == / 64
// 			my = (int)ry >> 6; // >> 6 == / 64
// 			printf("mx is: %d | my is: %d | dof is: %d\n", mx, my, dof);
// 			// mp = my * 8 + mx;
// 			// break;
// 			if (dof < 8 && mx < 8 && my < 8 && map[mx][my] == '1')
// 				break ;
// 			else
// 			{
// 				rx += xo;
// 				ry += yo;
// 			}
// 			dof++;
// 		}
// 		img = mlx_new_image(mlx, 8, 8);
// 		ft_memset(img->pixels, 255, img->width * img->height * BPP);
// 		mlx_image_to_window(mlx, img, rx, ry);
// 		i++;
// 	}
// }
