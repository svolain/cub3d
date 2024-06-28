/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_calc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:31:52 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/26 11:31:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static void	raydata_to_texdata(int tx, t_image img, t_vector *ray)
{
	static int	shade = 300;

	ray->x = tx;
	ray->img = img;
	ray->a = shade;
}

static void	vertical_delta_offset(int *height, t_vector *ray, t_cubed *game)
{
	ray->y = 0;
	ray->d = (float)game->asset[ray->img]->width / *height;
	if (*height > SCREEN_HEIGHT)
	{
		ray->y = (float)(*height - SCREEN_HEIGHT) / 2 * ray->d;
		*height = SCREEN_HEIGHT;
	}
}

static t_image	assing_wall_texture(t_vector *ray, t_cubed *game)
{
	int	map[2];

	get_map_position(map, ray->x, ray->y);
	if (get_map_element(map[X], map[Y], game) == MAP_CLOSED)
		return (IMG_DR);
	else if (ray->img == IMG_EA && ray->a > NORTH && ray->a < SOUTH)
		return (IMG_WE);
	else if (ray->img == IMG_SO && ray->a > WEST)
		return (IMG_NO);
	return (0);
}

static int	horizontal_position(t_vector *ray, t_cubed *game)
{
	if (ray->img == IMG_EA)
		return ((int)(ray->y) % game->asset[ray->img]->height);
	else
		return ((int)(ray->x) % game->asset[ray->img]->width);
}

void	calculate_wall(int *height, t_vector *ray, t_cubed *game)
{
	int		tx;
	t_image	img;

	tx = horizontal_position(ray, game);
	img = assing_wall_texture(ray, game);
	vertical_delta_offset(height, ray, game);
	raydata_to_texdata(tx, img, ray);
}
