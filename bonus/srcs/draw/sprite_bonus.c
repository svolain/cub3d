/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:39:35 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/26 11:31:43 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static int32_t	calculate_shade(float dy)
{
	static int	treshold = 520;
	static int	modifier = 510;
	float		intensity;

	if (dy <= treshold)
		return (COLOR_BLACK);
	intensity = modifier / (dy / 255.0f);
	return (get_rgba(0, 0, 0, intensity));
}

static void	draw_sprite(float *depth, t_camera *spr, t_camera *tex, t_cubed *game)
{
	int			screen[2];
	int32_t		color;
	int32_t		shade;
	mlx_image_t	*img;

	img = game->asset[(int)spr->a];
	screen[X] = spr->x - spr->dx / 2 - 1;
	while (++screen[X] < spr->x + spr->dx / 2)
	{
		screen[Y] = -1;
		tex->y = img->height;
		printf("screen x = %d | wall depth = %f | sprite dy = %f\n", screen[X], depth[10], spr->dy);
		while (++screen[Y] < spr->dy)
		{
			color = get_pixel_color(img, tex->x, tex->y);
			if (get_channel_color(color, GET_ALPHA))
			{
				shade = calculate_shade(spr->dy);
				color = get_alpha_blend(shade, color);
			}
			if (ft_valid_pixel(game->asset[IMG_OL], screen[X], spr->y - screen[Y]))
				mlx_put_pixel(game->asset[IMG_OL], screen[X], spr->y - screen[Y], color);
			tex->y -= tex->dy;
		}
		tex->x += tex->dx;
	}
}

static void	process_sprite(int map[2], float *depth, t_camera *cam, t_cubed *game)
{
	static int	sprite_limit = 5000;
	t_camera	texture;
	t_camera	sprite;

	calc_spr_scr(map, &sprite, cam);
	calc_spr_tex(map, &sprite, &texture, game);
	if (!sprite.dy || ft_in_sprite(map, cam, game)
		|| sprite.dy >= sprite_limit)
		return ;
	draw_sprite(depth, &sprite, &texture, game);
}

static void	calc_spr_walls(float *depth, t_camera *cam, float angle, t_cubed *game)
{
	t_vector	ray;
	int			column;

	column = 0;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (column < SCREEN_WIDTH)
	{
		ray.a = angle;
		calculate_ray(&ray, cam, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		depth[column] = ray.d;
		column++;
	}
}

void	draw_sprites(t_camera *cam, float angle, t_cubed *game)
{
	float	depth[SCREEN_WIDTH];
	int		map[2];
	char	c;

	(void)angle;
	map[X] = 0;
	calc_spr_walls(depth, cam, cam->a, game);
	while (map[X] < game->map->width)
	{
		map[Y] = 0;
		while (map[Y] < game->map->height)
		{
			c = get_map_element(map[X], map[Y], game);
			if (c == MAP_HEALTH || c == MAP_AMMO)
				process_sprite(map, depth, cam, game);
			map[Y]++;
		}
		map[X]++;
	}
}

/* static bool	is_behind_wall(
	int column, float dx, t_camera *cam, t_cubed *game) */
/* { */
/* 	t_vector	ray; */
/* 	float		angle; */
/**/
/* 	angle = cam->a; */
/* 	ft_rotate(&cam->a, FOV / 2, ROTATE_LEFT); */
/* 	ft_rotate(&cam->a, column * STEP_WINDOW, ROTATE_LEFT); */
/* 	printf("cam->a for ray calc = %f\n", cam->a); */
/* 	calculate_ray(&ray, cam, game); */
/* 	cam->a = angle; */
/* 	printf("dx = %f | ray.d = %f | cam->a = %f\n", dx, ray.d, cam->a); */
/* 	if (ray.d < dx) */
/* 		return true; */
/* 	return (false); */
/* } */
