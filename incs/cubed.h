/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/25 13:03:37 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <MLX42.h>
# include <libft.h>
# include <error.h>

# include <stdbool.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>

# define GAME_ASSETS 5

# define CELLSIZE 64
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define SCREEN_TITLE "cub3d"

# define PI 3.1415926535898

# define EAST 0
# define NORTH PI / 2
# define WEST PI
# define SOUTH 3 * PI / 2

# define FOV ft_degtorad(66)
# define DEGREE ft_degtorad(1)

# define STEP_ANGLE 0.05
# define STEP_MOVEMENT CELLSIZE / 8
# define STEP_WINDOW FOV / SCREEN_WIDTH
# define BPP sizeof(int)
# define MINIMAP_MAX 10

# define FMT_BOLD_RED	"\033[1;31m"
# define FMT_YELLOW		"\033[0;33m"
# define FMT_RESET		"\033[0m"

typedef enum e_check
{
	FAILURE = -1,
	SUCCESS = 0,
	X_COOR = 0,
	Y_COOR = 1,
	H_DIST = 0,
	V_DIST = 1
}	t_check;

typedef enum e_action
{
	ROTATE_LEFT,
	ROTATE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	GET_RED,
	GET_GREEN,
	GET_BLUE,
	GET_ALPHA
}	t_action;

typedef enum e_minimap
{
	FLOOR = 48,
	WALL = 49
}	t_minimap;

typedef enum e_element
{
	ELEM_NO,
	ELEM_SO,
	ELEM_WE,
	ELEM_EA,
	ELEM_BG = 4,
	ELEM_F = 4,
	ELEM_C
}	t_element;

typedef struct s_vector
{
	float	x;
	float	y;
	float	a;
	float	d;
}	t_vector;

/* typedef struct s_sprite */
/* { */
/* 	mlx_texture_t	*tex; */
/* 	mlx_image_t		*img; */
/* 	struct s_sprite	*next; */
/* }	t_sprite; */

typedef struct s_mapinfo
{
	char		**matrix;
	int			width;
	int			height;
	char		*file;
	int			fd;
	/* t_sprite	*img; */
	/* mlx_image_t	*mplayer; */
	/* mlx_image_t	*mwall; */
	/* mlx_image_t	*mfloor; */
	/* mlx_image_t	*msfloor; */
	int			endx;
	int			endy;
}	t_mapinfo;

typedef struct s_cubed
{
	t_vector	*cam;
	t_mapinfo	*map;
	/* t_sprite	*img; */
	mlx_image_t	*imgs;
	mlx_t		*mlx;
}	t_cubed;

//		Init
void	init_game(t_cubed *game, char *file);

//		Hooks
void	hook_close(void *param);
void	hook_keys(mlx_key_data_t keydata, void *param);
/* void	hook_keys(void *param); */

//		Calc
void	calculate_ray(t_vector *ray, t_cubed *game);

//		Draw
void	draw_walls(t_cubed *game);

//		Map
void	init_minimap(t_cubed *game);
void	draw_minimap(t_cubed *game, int flag);
void	move_minimap(t_cubed *game, t_action action);
void	change_mini_foor(t_cubed *game);

//		Error
void	error_exit(int errcode, char *errmsg, t_cubed *game);
void	error_fatal(int errcode, char *errmsg, t_cubed *game);

//		Free
void	free_exit(t_cubed *game, int excode);

//		Colors
void	color_image(mlx_image_t *image, int32_t r, int32_t g, int32_t b);
void	alpha_blend(mlx_image_t *image, int32_t alpha, uint32_t x, uint32_t y);
int32_t	get_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t	get_pixel(int32_t rgba, t_action action);

//		Utils
float	ft_degtorad(float degree);
void	ft_rotate(float *target, float angle, t_action action);
void	*safe_calloc(size_t n, t_cubed *game);
char	*ft_skip_whitespace(char *str);

//		Parsing
void	parse_map(t_cubed *game);

#endif
