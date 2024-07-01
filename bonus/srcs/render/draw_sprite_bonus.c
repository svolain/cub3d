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

static void	transparent_void(t_cubed *game)
{
	game->asset[IMG_OL]->enabled = false;
	ft_memset(game->asset[IMG_OL]->pixels,
		0, game->asset[IMG_OL]->width
		* game->asset[IMG_OL]->height * BPP);
	draw_screen_fx(COLOR_PICKUP, game);
	game->asset[IMG_OL]->enabled = true;
}

static int32_t	calculate_color(mlx_image_t *img, float scale, t_sprinfo *tex)
{
	static int	treshold = 510;
	int32_t		color;
	int32_t		shade;

	color = get_pixel_color(img, tex->x, tex->y);
	if (!get_channel_color(color, GET_ALPHA) || scale <= treshold)
		return (TRANSPARENT);
	shade = get_rgba(0, 0, 0, treshold / (scale / 255.0f));
	return (get_alpha_blend(shade, color));
}

static void	draw_pixels(float *dep,
	t_sprinfo *spr, t_sprinfo *tex, t_cubed *game)
{
	int32_t	color;
	float	scale;
	int		x;
	int		y;

	scale = spr->dx;
	x = spr->x - scale / 2 - 1;
	while (++x < spr->x + scale / 2)
	{
		y = -1;
		tex->y = spr->img->height;
		while (++y < scale)
		{
			if (x >= 0 && x < SCREEN_WIDTH && dep[x] < tex->z)
				color = TRANSPARENT;
			else
				color = calculate_color(spr->img, spr->dy, tex);
			if (ft_valid_pixel(game->asset[IMG_OL], x, spr->y - y))
				mlx_put_pixel(game->asset[IMG_OL], x, spr->y - y, color);
			tex->y -= tex->dy;
		}
		tex->x += tex->dx;
	}
}

static void	process_sprite(int map[2], float *dep, t_camera *cam, t_cubed *game)
{
	static int	size_limit = 5500;
	t_sprinfo	texture;
	t_sprinfo	sprite;

	calc_spr_scr(map, &sprite, cam);
	calc_spr_tex(map, &sprite, &texture, game);
	if (!sprite.dy)
		return ;
	else if (ft_in_sprite(map, cam, game)
		|| sprite.dy >= size_limit)
		return ((void)transparent_void(game));
	draw_pixels(dep, &sprite, &texture, game);
}

void	draw_sprites(t_camera *cam, t_cubed *game)
{
	float	depths[SCREEN_WIDTH];
	int		map[2];
	char	c;

	map[X] = 0;
	calc_spr_walls(depths, cam, game);
	while (map[X] < game->map->width)
	{
		map[Y] = 0;
		while (map[Y] < game->map->height)
		{
			c = get_map_element(map[X], map[Y], game);
			if (c == MAP_HEALTH || c == MAP_AMMO || c == MAP_EXIT)
				process_sprite(map, depths, cam, game);
			map[Y]++;
		}
		map[X]++;
	}
}
