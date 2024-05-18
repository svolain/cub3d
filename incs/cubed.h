/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/16 16:09:08 by jmertane         ###   ########.fr       */
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
# define DEGREE PI / 360

# define EAST 0
# define NORTH PI / 2
# define WEST PI
# define SOUTH 3 * PI / 2

# define FOV PI / 2

# define STEP_ANGLE 0.05
# define STEP_MOVEMENT CELLSIZE / 8
# define BPP sizeof(int)

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
	MOVE_RIGHT
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

//		Calculations
void	calculate_rays(t_cubed *game);

//		Hooks
void	keyhooks(mlx_key_data_t keydata, void *param);

//		Error handling
void	error_exit(int errcode, char *errmsg, t_cubed *game);
void	error_fatal(int errcode, char *errmsg, t_cubed *game);

//		Freeing
void	close_window(void *param);
void	free_exit(t_cubed *game, int excode);

//		Utilities
float	degree_to_rad(float degree);
void	check_rotation(float *angle, t_action action);
void	*safe_calloc(size_t n, t_cubed *game);

#endif
