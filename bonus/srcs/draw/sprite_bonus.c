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

static int32_t	calculate_color(mlx_image_t *img, float scale, t_camera *tex)
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

static void	draw_pixels(float *dep, t_camera *spr, t_camera *tex, t_cubed *game)
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
		tex->y = game->asset[(int)spr->a]->height;
		while (++y < scale)
		{
			if (x >= 0 && x < SCREEN_WIDTH && dep[x] < tex->z)
				color = TRANSPARENT;
			else
				color = calculate_color(game->asset[(int)spr->a], spr->dy, tex);
			if (ft_valid_pixel(game->asset[IMG_OL], x, spr->y - y))
				mlx_put_pixel(game->asset[IMG_OL], x, spr->y - y, color);
			tex->y -= tex->dy;
		}
		tex->x += tex->dx;
	}
}

static void	process_sprite(int map[2], float *dep, t_camera *cam, t_cubed *game)
{
	static int	size_limit = 5000;
	t_camera	texture;
	t_camera	sprite;

	calc_spr_scr(map, &sprite, cam);
	calc_spr_tex(map, &sprite, &texture, game);
	if (!sprite.dy || ft_in_sprite(map, cam, game)
		|| sprite.dy >= size_limit)
		return ;
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
			if (c == MAP_HEALTH || c == MAP_AMMO)
				process_sprite(map, depths, cam, game);
			map[Y]++;
		}
		map[X]++;
	}
}
