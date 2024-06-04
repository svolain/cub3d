/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 06:47:04 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/03 06:48:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	draw_space(int start_point, int end_point, int x, t_cubed *game)
{
	int	floor;
	int	roof;

	roof = -1;
	floor = SCREEN_HEIGHT + 1;
	while (roof++ < start_point)
	{
		if (roof < MAPCELL * MAPGRID && x < MAPCELL * MAPGRID)
			continue ;
		ft_putpixel(x, roof, game->color[COL_C], game);
	}
	while (floor-- > end_point)
		ft_putpixel(x, floor, game->color[COL_F], game);
}

static void	draw_column(int x, int height, t_vector *ray, t_cubed *game)
{
	int		point[2];
	int32_t	color;

	point[A] = SCREEN_HEIGHT / 2 - height / 2 - 1;
	point[B] = SCREEN_HEIGHT / 2 + height / 2;
	draw_space(point[A], point[B], x, game);
	while (point[A]++ < point[B])
	{
		color = get_color(game->image[ray->img], ray->x, ray->y);
		ray->y += ray->d;
		if (point[A] < MAPCELL * MAPGRID && x < MAPCELL * MAPGRID)
			continue ;
		ft_putpixel(x, point[A], color, game);
	}
}

static void	calculate_draw(int *height, t_vector *ray, t_cubed *game)
{
	int map[2];

	get_position(map, ray->x, ray->y);
	if (ray->img == IMG_EA)
		ray->x = (int)(ray->y) % game->image[ray->img]->width;
	else
		ray->x = (int)(ray->x) % game->image[ray->img]->width;
	if (game->map->matrix[map[Y]][map[X]] == MAP_CLOSED)
		ray->img = IMG_FL;
	else if (ray->img == IMG_EA && ray->a > NORTH && ray->a < SOUTH)
		ray->img = IMG_WE;
	else if (ray->img == IMG_SO && ray->a > WEST)
		ray->img = IMG_NO;
	ray->y = 0;
	ray->d = (float)game->image[ray->img]->width / *height;
	if (*height > SCREEN_HEIGHT)
	{
		ray->y = (float)(*height - SCREEN_HEIGHT) / 2 * ray->d;
		*height = SCREEN_HEIGHT;
	}
}

static bool	frame_elapsed(t_cubed *game)
{
 	static double	frame = 0;

 	frame += game->mlx->delta_time;
	printf("frame = %f\n", frame);
 	if (frame < 10.0f)
 		return (false);
 	frame -= 10.0f;
	return (true);
}

void	animate_door(int column, t_vector *ray, t_cubed *game)
{
	int	height;

	while (!frame_elapsed(game))
	 	true ;
	calculate_ray(ray, game);
	fix_fisheye(ray, game);
	height = CELLSIZE * SCREEN_HEIGHT / ray->d;
	calculate_draw(&height, ray, game);
	draw_column(column, height, ray, game);
}

int	find_rightedge(t_vector *right, t_cubed *game)
{
	float	angle;
	int		column;
	int		map[2];

	column = SCREEN_WIDTH - 1;
	angle = game->cam->a;
	ft_rotate(&angle, FOV / 2, ROTATE_RIGHT);
	while (column >= 0)
	{
		right->a = angle;
		calculate_ray(right, game);
		get_position(map, right->x, right->y);
		if (game->map->matrix[map[Y]][map[X]] == MAP_CLOSED)
			break ;
		ft_rotate(&angle, STEP_WINDOW, ROTATE_LEFT);
		column--;
	}
	game->map->matrix[map[Y]][map[X]] = MAP_OPENED;
	right->a = game->cam->a;
	return (column);
}

int	find_leftedge(t_vector *left, t_cubed *game)
{
	float	angle;
	int		column;
	int		map[2];

	column = 0;
	angle = game->cam->a;
	ft_rotate(&angle, FOV / 2, ROTATE_LEFT);
	while (column < SCREEN_WIDTH)
	{
		left->a = angle;
		calculate_ray(left, game);
		get_position(map, left->x, left->y);
		if (game->map->matrix[map[Y]][map[X]] == MAP_CLOSED)
			break ;
		ft_rotate(&angle, STEP_WINDOW, ROTATE_RIGHT);
		column++;
	}
	left->a = game->cam->a;
	return (column);
}

void	open_door(t_cubed *game)
{
	t_vector	left;
	t_vector	right;
	int			end[2];
	int			mid[2];

	end[A] = find_leftedge(&left, game);
	end[B] = find_rightedge(&right, game);
	mid[A] = (end[A] + end[B]) / 2;
	mid[B] = (end[A] + end[B]) / 2;
	game->anims[ANIM_OPEN] = true;
	while (mid[A] >= end[A] && mid[B] <= end[B])
	{
		animate_door(mid[A]--, &left, game);
		ft_rotate(&left.a, STEP_WINDOW, ROTATE_RIGHT);
		animate_door(mid[B]++, &right, game);
		ft_rotate(&right.a, STEP_WINDOW, ROTATE_LEFT);
	}
	game->anims[ANIM_OPEN] = false;
}
