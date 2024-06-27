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

/* static int32_t	calculate_shade(float dy, int32_t color) */
/* { */
/* 	static int	treshold = 520; */
/* 	static int	modifier = 510; */
/* 	float		intensity; */
/**/
/* 	if (!get_channel_color(color, GET_ALPHA)) */
/* 		return (TRANSPARENT); */
/* 	else if (dy <= treshold) */
/* 		return (COLOR_BLACK); */
/* 	intensity = modifier / (dy / 255.0f); */
/* 	return (get_rgba(0, 0, 0, intensity)); */
/* } */

static void	draw_pixels(t_camera *sprite, t_camera *tex, t_cubed *game)
{
	int32_t	color;
	/* int32_t	shade; */
	int		x;
	int		y;

	x = sprite->x - sprite->dx / 2;
	while (x < sprite->x + sprite->dx / 2)
	{
		y = 0;
		tex->y = game->asset[(int)sprite->a]->height;
		while (y < sprite->dy)
		{
			color = get_pixel_color(game->asset[(int)sprite->a], tex->x, tex->y);
			/* shade = calculate_shade(sprite->dy, color); */
			/* color = get_alpha_blend(shade, color); */
			if (ft_valid_pixel(game->asset[IMG_OL], x, sprite->y - y))
				mlx_put_pixel(game->asset[IMG_OL], x, sprite->y - y, color);
			tex->y -= tex->dy;
			y++;
		}
		tex->x += tex->dx;
		x++;
	}
}

static t_image	assign_texture(char c)
{
	if (c == MAP_AMMO)
		return (IMG_AM);
	else
		return (IMG_HL);
}

static void	calculate_texture(char c, t_camera *sprite, t_camera *tex, t_cubed *game)
{
	static int	scale_factor = 2000;
	int			size;

	sprite->a = assign_texture(c);
	size = game->asset[(int)sprite->a]->height;
	sprite->dx = size / sprite->dy * scale_factor;
	sprite->dy = sprite->dx;
	tex->dx = size / sprite->dx;
	tex->dy = size / sprite->dy;
	tex->y = size;
	tex->x = 0;
}

static void	calculate_sprite(int x, int y, t_camera *sprite, t_camera *cam)
{
	static float	x_scale = -2000.0f;
	static float	y_scale = 400.0f;

	x = x * CELLSIZE + CELLSIZE / 2;
	y = y * CELLSIZE + CELLSIZE / 2;
	sprite->x = x - cam->x;
	sprite->y = y - cam->y;
	sprite->z = (float)SCREEN_HEIGHT / 2;
	sprite->dx = sprite->y * -cos(cam->a) + sprite->x * sin(cam->a);
	sprite->dy = sprite->x * cos(cam->a) + sprite->y * sin(cam->a);
	sprite->x = sprite->dx;
	sprite->y = sprite->dy;
	sprite->x = sprite->x * x_scale / sprite->y + SCREEN_WIDTH / 2;
	sprite->y = sprite->z * y_scale / sprite->y + SCREEN_HEIGHT / 2;
}

/* static bool	player_on_element(int x, int y, t_camera *cam, t_cubed *game) */
/* { */
/* 	int	player[2]; */
/**/
/* 	get_map_position(player, cam->x, cam->y); */
/* 	if (player[X] == x && player[Y] == y) */
/* 	{ */
/* 		set_map_element(x, y, MAP_FLOOR, game); */
/* 		return (true); */
/* 	} */
/* 	return (false); */
/* } */

static void	draw_sprite(int x, int y, t_camera *cam, t_cubed *game)
{
	t_camera	texture;
	t_camera	sprite;
	char		c;

	/* if (player_on_element(x, y, cam, game)) */
	/* 	return ; */
	c = get_map_element(x, y, game);
	calculate_sprite(x, y, &sprite, cam);
	calculate_texture(c, &sprite, &texture, game);
	draw_pixels(&sprite, &texture, game);
}

void	draw_sprites(t_camera *cam, t_cubed *game)
{
	char	c;
	int		x;
	int		y;

	x = 0;
	while (x < game->map->width)
	{
		y = 0;
		while (y < game->map->height)
		{
			c = get_map_element(x, y, game);
			/* if (ft_strchr(CHARSET_SPRITE, c)) */
			if (c == MAP_HEALTH || c == MAP_AMMO)
				draw_sprite(x, y, cam, game);
			/* if (game_over(game)) */
			/* 	return ; */
			y++;
		}
		x++;
	}
}
