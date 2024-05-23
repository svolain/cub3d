/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:35:51 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/18 22:04:22 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	draw_segment(int height, int x, mlx_image_t *walld)
{
	int	a;
	int	b;

	a = SCREEN_HEIGHT / 2 - height / 2;
	b = SCREEN_HEIGHT / 2 + height / 2;
	while (a < b)
	{
		mlx_put_pixel(walld, x, a++, 255);
	}
}

static void	fix_fisheye(t_vector *ray, t_cubed *game)
{
	float	angle;

	angle = game->cam->a;
	ft_rotate(&angle, ray->a, ROTATE_LEFT);
	ray->dist *= cos(angle);
}

void	draw_walls(t_cubed *game)
{
	mlx_image_t	*walld;
	walld = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	color_image(walld, 0, 100, 200);
	mlx_image_to_window(game->mlx, walld, 0, 0);

	t_vector	*ray;
	float		angle;
	int			height;
	int			x;

	x = 0;
	angle = game->cam->a;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	ray = safe_calloc(sizeof(t_vector), game);
	while (x < SCREEN_WIDTH)
	{
		ray->a = angle;
		calculate_ray(ray, game);
		fix_fisheye(ray, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		height = CELLSIZE * SCREEN_HEIGHT / ray->dist;
		if (height > SCREEN_HEIGHT)
			height = SCREEN_HEIGHT;
		draw_segment(height, x, walld);
		x++;
	}
	free(ray);
}
