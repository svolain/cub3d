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

#include <cubed.h>

static int32_t	calculate_shade(int row, int32_t color)
{
	static int	treshold = 450;
	static int	modifier = 140;
	float		intensity;

	if (row <= SCREEN_HEIGHT - treshold)
		return (COLOR_BLACK);
	else
		intensity = (float)row / SCREEN_HEIGHT * 255.0f;
	return (get_alpha_blend(get_rgba(0, 0, 0, modifier - intensity), color));
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
	int32_t	shade;
	int32_t	item;
	int		row;

	row = SCREEN_HEIGHT / 2 + height / 2 - 1;
	while (row < SCREEN_HEIGHT)
	{
		calculate_draw(row, tex, cam, game);
		shade = calculate_shade(row, game->color[COL_FL]);
		item = get_alpha_blend(shade, get_pixel_color
				(game->asset[IMG_HL], tex[X], tex[Y]));
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
		if (!calculate_ray(&ray, cam, game, CHARSET_SPRITE))
			continue ;
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
