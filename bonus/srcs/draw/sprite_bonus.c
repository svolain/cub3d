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

static int32_t	calculate_shade(float spry)
{
	static int	treshold = 520;
	static int	modifier = 510;
	float		intensity;

	if (spry <= treshold)
		return (COLOR_BLACK);
	intensity = modifier / (spry / 255.0f);
	return (get_rgba(0, 0, 0, intensity));
}

static int32_t	calculate_color(mlx_image_t *img, t_camera *spr, t_camera *tex)
{
	int32_t		color;
	int32_t		shade;

	color = get_pixel_color(img, tex->x, tex->y);
	if (get_channel_color(color, GET_ALPHA))
	{
		shade = calculate_shade(spr->dy);
		color = get_alpha_blend(shade, color);
	}
	return (color);
}

/* printf("screen x = %d | wall depth = %f | sprite dy = %f\n", x, pit[10], spr->dy); */
static void	draw_sprite(float *pit, t_camera *spr, t_camera *tex, t_cubed *game)
{
	int32_t	color;
	int		x;
	int		y;

	x = spr->x - spr->dx / 2;
	while (x < spr->x + spr->dx / 2)
	{
		y = 0;
		tex->y = game->asset[(int)spr->a]->height;
		while (y < spr->dy)
		{
			color = calculate_color(game->asset[(int)spr->a], spr, tex);
			if (ft_valid_pixel(game->asset[IMG_OL], x, spr->y - y))
				mlx_put_pixel(game->asset[IMG_OL], x, spr->y - y, color);
			tex->y -= tex->dy;
			y++;
		}
		tex->x += tex->dx;
		x++;
	}
}

static void	process_sprite(int map[2], float *pit, t_camera *cam, t_cubed *game)
{
	static int	sprite_limit = 5000;
	t_camera	texture;
	t_camera	sprite;

	calc_spr_scr(map, &sprite, cam);
	calc_spr_tex(map, &sprite, &texture, game);
	if (!sprite.dy || ft_in_sprite(map, cam, game)
		|| sprite.dy >= sprite_limit)
		return ;
	draw_sprite(pit, &sprite, &texture, game);
}

void	draw_sprites(t_camera *cam, float angle, t_cubed *game)
{
	float	pit[SCREEN_WIDTH];
	int		map[2];
	char	c;

	(void)angle;
	map[X] = 0;
	calc_spr_walls(pit, cam, game);
	while (map[X] < game->map->width)
	{
		map[Y] = 0;
		while (map[Y] < game->map->height)
		{
			c = get_map_element(map[X], map[Y], game);
			if (c == MAP_HEALTH || c == MAP_AMMO)
				process_sprite(map, pit, cam, game);
			map[Y]++;
		}
		map[X]++;
	}
}
