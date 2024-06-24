/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:39:35 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/21 09:39:54 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static void	update_ray_data(t_vector *vec, t_vector *ray, bool horizontal)
{
	ray->x = vec->x;
	ray->y = vec->y;
	ray->d = vec->d;
	if (horizontal)
		ray->img = IMG_SO;
	else
		ray->img = IMG_EA;
}

static void	get_collosion_point(t_vector *vec, t_camera *cam, t_cubed *game)
{
	while (true)
	{
		if (!ft_inside_map(vec->x, vec->y, game)
			|| ft_in_charset(vec->x, vec->y, CHARSET_WALL, game))
			break ;
		vec->x += cam->dx;
		vec->y += cam->dy;
	}
}

static void	calculate_vertical(t_vector *vec, t_camera *cam, float angle)
{
	float	ntan;

	ntan = -tan(angle);
	if (angle > NORTH && angle < SOUTH)
	{
		vec->x = (int)cam->x / CELLSIZE * CELLSIZE - 0.001f;
		cam->dx = -CELLSIZE;
	}
	else
	{
		vec->x = (int)cam->x / CELLSIZE * CELLSIZE + CELLSIZE;
		cam->dx = CELLSIZE;
	}
	vec->y = (cam->x - vec->x) * ntan + cam->y;
	cam->dy = -cam->dx * ntan;
}

static void	calculate_horizontal(t_vector *vec, t_camera *cam, float angle)
{
	float	atan;

	atan = 1 / -tan(angle);
	if (angle > WEST)
	{
		vec->y = (int)cam->y / CELLSIZE * CELLSIZE - 0.001f;
		cam->dy = -CELLSIZE;
	}
	else
	{
		vec->y = (int)cam->y / CELLSIZE * CELLSIZE + CELLSIZE;
		cam->dy = CELLSIZE;
	}
	vec->x = (cam->y - vec->y) * atan + cam->x;
	cam->dx = -cam->dy * atan;
}

static void	calculate_sprite(t_vector *ray, t_camera *cam, t_cubed *game)
{
	t_vector	vec[2];

	calculate_horizontal(&vec[H], cam, ray->a);
	get_collosion_point(&vec[H], cam, game);
	calculate_vertical(&vec[V], cam, ray->a);
	get_collosion_point(&vec[V], cam, game);
	vec[H].d = sqrtf(powf((vec[H].x - cam->x), 2)
			+ powf((vec[H].y - cam->y), 2));
	vec[V].d = sqrtf(powf((vec[V].x - cam->x), 2)
			+ powf((vec[V].y - cam->y), 2));
	if (vec[H].d < vec[V].d)
		update_ray_data(&vec[H], ray, true);
	else
		update_ray_data(&vec[V], ray, false);
}











static void	calculate_draw(int row, float *tex, t_camera *cam, t_cubed *game)
{
	float	pp;
	float	dy;
	float	angle;

	angle = cos(fabs(cam->a - cam->dy));
	pp = (float)SCREEN_WIDTH / tan(FOV / 2);
	dy = row - (float)SCREEN_HEIGHT / 2.0f;
	tex[X] = cam->x * 1.4f;
	tex[Y] = -cam->y * 1.4f;
	tex[X] += cos(cam->dy) * pp * 64 / dy / angle;
	tex[Y] -= sin(cam->dy) * pp * 64 / dy / angle;
	tex[X] = (int)tex[X] % game->asset[IMG_FL]->width;
	tex[Y] = (int)tex[Y] % game->asset[IMG_FL]->height;
}

static void	draw_column(int column, int height, t_camera *cam, t_cubed *game)
{
	float	tex[2];
	int32_t	item;
	int		row;

	row = SCREEN_HEIGHT / 2 + height / 2 - 1;
	while (row < SCREEN_HEIGHT)
	{
		calculate_draw(row, tex, cam, game);
		item = get_pixel_color(game->asset[IMG_HL], tex[X], tex[Y]);
		ft_put_pixel(column, row, item, game->asset[IMG_BG]);
		row++;
	}
}

void	draw_sprites(t_camera *cam, float angle, t_cubed *game)
{
	t_vector	ray;
	int			height;
	int			column;

	column = -1;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (++column < SCREEN_WIDTH)
	{
		ray.a = angle;
		calculate_sprite(&ray, cam, game);
		fix_fisheye(&ray, cam->a);
		cam->dy = ray.a;
		height = CELLSIZE * SCREEN_HEIGHT / ray.d;
		if (height < SCREEN_HEIGHT)
			draw_column(column, height, cam, game);
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
	}
}

/* void	draw_sprites(t_camera *cam, float angle, t_cubed *game) */
/* { */
/* 	(void)angle; */
/**/
/* 	float spx = 23 * CELLSIZE; */
/* 	float spy = 3 * CELLSIZE; */
/* 	float spz = 20; */
/**/
/* 	float sx=spx-cam->x; */
/* 	float sy=spy-cam->y; */
/* 	float sz=spz; */
/**/
/* 	float CS=cos(cam->a); */
/* 	float SN=sin(cam->a); */
/**/
/* 	float a=sy*CS+sx*SN; */
/* 	float b=sx*CS-sy*SN; */
/**/
/* 	sx=a; */
/* 	sy=b; */
/**/
/* 	sx=(sx*100.0/sy)+(SCREEN_HEIGHT/2); */
/* 	sy=(sz*100.0/sy)+(SCREEN_WIDTH/2); */
/**/
/* 	float scale = CELLSIZE / b * 100.0f; */
/* 	int x; */
/* 	int y; */
/**/
/* 	ft_memset(game->asset[IMG_OL]->pixels, */
/* 		0, game->asset[IMG_OL]->height */
/* 		* game->asset[IMG_OL]->width * BPP); */
/**/
/* 	for(x=sx-scale/2;x<sx+scale/2;x++) */
/* 	{ */
/* 		for(y=0;y<scale;y++) */
/* 		{ */
/* 			ft_put_pixel(x, sy-y, COLOR_RAY, game->asset[IMG_OL]); */
/* 		} */
/* 	} */
/* } */
