/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/20 16:45:55 by jmertane         ###   ########.fr       */
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

# define CELLSIZE 64
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define SCREEN_TITLE "cub3d"

# define PI 3.1415926535898

# define EAST 0
# define NORTH PI / 2
# define WEST PI
# define SOUTH 3 * PI / 2

# define STEP_ANGLE 0.05
# define STEP_MOVEMENT CELLSIZE / 8
# define DEGREE degree_to_radian(1)
# define FOV degree_to_radian(66)
# define BPP sizeof(int)
# define MINIMAP_MAX 10

# define FMT_BOLD_RED	"\033[1;31m"
# define FMT_YELLOW		"\033[0;33m"
# define FMT_RESET		"\033[0m"

typedef enum e_checker
{
	FAILURE = -1,
	SUCCESS = 0,
	X = 0,
	Y = 1,
	H = 0,
	V = 1
}	t_checker;

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

typedef enum e_element
{
	FLOOR = 48,
	WALL
}	t_element;

typedef struct s_camera
{
	float	x;
	float	y;
	float	a;
}	t_camera;

typedef struct s_vector
{
	float	x;
	float	y;
	float	a;
	float	dist;
}	t_vector;

typedef struct s_texture
{
	t_vector			*vec;
	float				scale;
	mlx_texture_t		*tex;
	mlx_image_t			*img;
	int					fd;
	struct s_texture	*next;
}	t_texture;

typedef struct s_mapinfo
{
	char		**matrix;
	char		*file;
	int			width;
	int			height;
	t_texture	*tex;
	int			fd;
	mlx_image_t	*mplayer;
	mlx_image_t	*mwall;
	mlx_image_t	*mfloor;
	int			endx;
	int			endy;
}	t_mapinfo;

typedef struct s_cubed
{
	t_camera	*cam;
	t_mapinfo	*map;
	t_texture	*tex;
	mlx_t		*mlx;
}	t_cubed;

//		Init
void	init_game(t_cubed *game, char *file);

//		Hooks
void	hook_close(void *param);
void	hook_keys(mlx_key_data_t keydata, void *param);
/* void	hook_keys(void *param); */

//		Calculations
void	calculate_rays(t_cubed *game);

//		Drawing
void	draw_floor(t_cubed *game);
void	draw_walls(t_cubed *game, t_vector *vec, int i);

//		Minimap
void	init_minimap(t_cubed *game);
void	draw_minimap(t_cubed *game);
void	move_minimap(t_cubed *game, t_action action);

//		Error handling
void	error_exit(int errcode, char *errmsg, t_cubed *game);
void	error_fatal(int errcode, char *errmsg, t_cubed *game);

//		Freeing
void	free_exit(t_cubed *game, int excode);

//		Coloring
void	color_image(mlx_image_t *image, int32_t r, int32_t g, int32_t b);
void	alpha_blend(mlx_image_t *image, int32_t alpha, uint32_t x, uint32_t y);
int32_t	get_rgba(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t	get_pixel(int32_t rgba, t_action action);

//		Utilities
float	degree_to_radian(float degree);
void	update_rotation(float *target, float angle, t_action action);
void	*safe_calloc(size_t n, t_cubed *game);

#endif
