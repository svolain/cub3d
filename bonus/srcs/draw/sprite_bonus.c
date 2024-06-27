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

static void	draw_pixels(t_camera *sprite, t_camera *texture, t_cubed *game)
{
	int			screen[2];
	int32_t		color;
	int32_t		shade;
	mlx_image_t	*img;

	img = game->asset[(int)sprite->a];
	screen[X] = sprite->x - sprite->dx / 2 - 1;
	while (++screen[X] < sprite->x + sprite->dx / 2)
	{
		screen[Y] = -1;
		texture->y = img->height;
		while (++screen[Y] < sprite->dy)
		{
			color = get_pixel_color(img, texture->x, texture->y);
			texture->y -= texture->dy;
			if (get_channel_color(color, GET_ALPHA))
			{
				shade = calculate_shade(sprite->dy);
				color = get_alpha_blend(shade, color);
			}
			if (ft_valid_pixel(game->asset[IMG_OL], screen[X], sprite->y - screen[Y]))
				mlx_put_pixel(game->asset[IMG_OL], screen[X], sprite->y - screen[Y], color);
		}
		texture->x += texture->dx;
	}
}

static void	draw_sprite(int map[2], t_camera *cam, t_cubed *game)
{
	static int	sprite_limit = 5000;
	t_camera	texture;
	t_camera	sprite;

	calc_spr_scr(map, &sprite, cam);
	calc_spr_tex(map, &sprite, &texture, game);
	if (!sprite.dy || ft_in_sprite(map, cam, game)
		|| sprite.dy >= sprite_limit)
		return ;
	draw_pixels(&sprite, &texture, game);
}

void	draw_sprites(t_camera *cam, float angle, t_cubed *game)
{
	int		map[2];
	char	c;

	(void)angle;
	map[X] = 0;
	while (map[X] < game->map->width)
	{
		map[Y] = 0;
		while (map[Y] < game->map->height)
		{
			c = get_map_element(map[X], map[Y], game);
			if (c == MAP_HEALTH || c == MAP_AMMO)
				draw_sprite(map, cam, game);
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
