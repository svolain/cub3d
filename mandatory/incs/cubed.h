/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/07 13:15:43 by vsavolai         ###   ########.fr       */
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

# define GAME_ASSETS 4
# define GAME_COLORS 2

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define SCREEN_TITLE "cub3d"

# define MAXSIZE 500
# define CELLSIZE 64
# define BUMP_BUFFER 20
# define SCALE_FACTOR 2
# define MAPGRID 10

# define CHARSET_ALLOWED	"01NSEW "
# define CHARSET_PLAYER		"NSEW"
# define CHARSET_MOVEABLE	"0"

# define PI 3.1415926535898f

# define EAST 0
# define NORTH PI / 2.0f
# define WEST PI
# define SOUTH 3.0f * PI / 2.0f

# define FOV ft_degtorad(66)
# define DEGREE ft_degtorad(1)

# define STEP_ANGLE 0.04f
# define STEP_MOVEMENT 5.0f
# define STEP_WINDOW FOV / SCREEN_WIDTH

# define MAPCELL CELLSIZE / SCALE_FACTOR
# define MAPSIZE MAPCELL * MAPGRID

# define BPP sizeof(int32_t)

# define FMT_BOLD_RED	"\033[1;31m"
# define FMT_YELLOW		"\033[0;33m"
# define FMT_RESET		"\033[0m"

typedef enum e_check
{
	FAILURE = -1,
	SUCCESS = 0,
	X = 0,
	Y = 1,
	H = 0,
	V = 1,
	A = 0,
	B = 1,
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
	MAP_FLOOR = 48,
	MAP_WALL = 49,
}	t_minimap;

typedef enum e_image
{
	IMG_NO,
	IMG_SO,
	IMG_WE,
	IMG_EA,
}	t_image;

typedef enum e_color
{
	COL_F,
	COL_C
}	t_color;

typedef struct s_vector
{
	float		x;
	float		y;
	float		a;
	float		d;
	t_image		img;
}	t_vector;

typedef struct s_camera
{
	float		x;
	float		y;
	float		a;
	float		dx;
	float		dy;
}	t_camera;

typedef struct s_mapinfo
{
	char		**matrix;
	int			width;
	int			height;
	char		*filename;
	int			filefd;
}	t_mapinfo;

typedef struct s_cubed
{
	t_camera	*cam;
	t_mapinfo	*map;
	char		*gnl;
	mlx_t		*mlx;
	mlx_image_t	*canvas;
	mlx_image_t	*image[GAME_ASSETS];
	int32_t		color[GAME_COLORS];
}	t_cubed;

//		Parse
void	parse_filename(t_cubed *game);
void	open_infile(t_cubed *game);
void	parse_elements(t_cubed *game);
void	parse_mapinfo(t_cubed *game);
void	check_walls(t_cubed *game, char **duplex);
void	check_inward(t_cubed *game, char **map);
char	*ft_skipspaces(char *start, t_cubed *game);
bool	ft_isemptyline(char *str);

//		Load
void	load_sprite(t_image index, char *start, bool *loaded, t_cubed *game);
void	load_color(t_color index, char *start, bool *loaded, t_cubed *game);

//		Hook
void	hook_close(void *param);
void	hook_movement(void *param);
void	hook_action(mlx_key_data_t keydata, void *param);
void	move_camera(t_cubed *game, t_action action);
void	rotate_camera(t_cubed *game, t_action action);

//		Render
void	render_scenario(void *param);
void	calculate_ray(t_vector *ray, t_cubed *game);
int32_t	get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
void	ft_put_pixel(int x, int y, int32_t color, t_cubed *game);
int32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

//		Rotate
void	ft_rotate(float *target, float angle, t_action action);
void	fix_fisheye(t_vector *ray, t_cubed *game);
float	ft_degtorad(float degree);

//		Error
void	error_exit(int errcode, char *errmsg, t_cubed *game);
void	error_fatal(int errcode, char *errmsg, t_cubed *game);

//		Free
void	free_exit(t_cubed *game, int excode);
void	free_single(char **str);
void	free_double(char ***str);

//		String
char	*safe_substr(char *stt, char *end, t_cubed *game);
char	*safe_strjoin(char *s1, char *s2, t_cubed *game);
char	**safe_split(char *str, char c, t_cubed *game);

//		Safe
void	*safe_calloc(size_t n, t_cubed *game);
void	safe_draw(mlx_image_t *img, int x, int y, t_cubed *game);
void	*safe_tex(char *file, bool allocated, t_cubed *game);
void	*safe_img(uint32_t w, uint32_t h, mlx_texture_t *t, t_cubed *game);

#endif
