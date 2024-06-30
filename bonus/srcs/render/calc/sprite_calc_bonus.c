/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:52:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/30 11:44:50 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static mlx_image_t	*get_sprite_texture(char element, t_cubed *game)
{
	if (element == MAP_AMMO)
		return (game->asset[IMG_AM]);
	else if (element == MAP_HEALTH)
		return (game->asset[IMG_HL]);
	else if (element == MAP_EXIT)
		return (get_portal_frame(game->sprite[SPRT_GATE], game));
	return (NULL);
}

void	calc_spr_tex(int map[2], t_sprinfo *spr, t_sprinfo *tex, t_cubed *game)
{
	static int	scale_factor = 2000;
	static int	size_limit = 5000;
	int			size;
	float		scale;

	tex->z = spr->dy;
	spr->img = get_sprite_texture(get_map_element(map[X], map[Y], game), game);
	size = spr->img->height;
	scale = size / spr->dy * scale_factor;
	if (scale < 0)
		scale = 0;
	if (scale > size_limit)
		scale = size_limit;
	spr->dx = scale;
	spr->dy = scale;
	tex->dx = size / spr->dx;
	tex->dy = size / spr->dy;
	tex->y = size;
	tex->x = 0;
}

void	calc_spr_scr(int map[2], t_sprinfo *spr, t_camera *cam)
{
	static float	x_scale = -2000.0f;
	static float	y_scale = 400.0f;
	int				x;
	int				y;

	x = map[X] * CELLSIZE + CELLSIZE / 2;
	y = map[Y] * CELLSIZE + CELLSIZE / 2;
	spr->x = x - cam->x;
	spr->y = y - cam->y;
	spr->z = (float)SCREEN_HEIGHT / 2;
	spr->dx = spr->y * -cos(cam->a) + spr->x * sin(cam->a);
	spr->dy = spr->x * cos(cam->a) + spr->y * sin(cam->a);
	spr->x = spr->dx;
	spr->y = spr->dy;
	spr->x = spr->x * x_scale / spr->y + SCREEN_WIDTH / 2;
	spr->y = spr->z * y_scale / spr->y + SCREEN_HEIGHT / 2;
}

void	calc_spr_walls(float *depth, t_camera *cam, t_cubed *game)
{
	t_vector	ray;
	float		angle;
	int			column;

	column = 0;
	angle = cam->a;
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
