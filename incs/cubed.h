/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/05 16:33:50 by vsavolai         ###   ########.fr       */
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

# define GAME_ASSETS 7
# define GAME_COLORS 2
# define GAME_ANIMS 10
# define GAME_STATS 2

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define SCREEN_TITLE "cub3d"

# define FPS 30.0f
# define MAXSIZE 500
# define CELLSIZE 64
# define BUMP_BUFFER 20
# define SCALE_FACTOR 2
# define MAPGRID 10

# define CHARSET_ALLOWED	"01CONSEW "
# define CHARSET_PLAYER		"NSEW"
# define CHARSET_MOVEABLE	"0O"

# define PI 3.1415926535898f

# define EAST 0
# define NORTH PI / 2.0f
# define WEST PI
# define SOUTH 3.0f * PI / 2.0f

# define FOV ft_degtorad(66)
# define DEGREE ft_degtorad(1)

# define STEP_ANGLE 0.02f
# define STEP_MOVEMENT 2.0f
# define STEP_WINDOW FOV / SCREEN_WIDTH

# define MAPCELL CELLSIZE / SCALE_FACTOR
# define MAPSIZE MAPCELL * MAPGRID

# define BPP sizeof(int32_t)

# define TEX_FLOOR		"./textures/floor.png"
# define TEX_ROOF		"./textures/roof.png"
# define TEX_DOOR		"./textures/door.png"

# define TEX_IDLE		"./textures/player_stand.png"
# define TEX_WALK1		"./textures/player_walk1.png"
# define TEX_WALK2		"./textures/player_walk2.png"

# define TEX_SHOT1		"./textures/shotgun1.png"
# define TEX_SHOT2		"./textures/shotgun2.png"
# define TEX_SHOT3		"./textures/shotgun3.png"
# define TEX_SHOT4		"./textures/shotgun4.png"
# define TEX_SHOT5		"./textures/shotgun5.png"


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
	B = 1
}	t_check;

typedef enum e_action
{
	ROTATE_LEFT,
	ROTATE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	DOOR_OPEN,
	DOOR_CLOSE,
	GET_RED,
	GET_GREEN,
	GET_BLUE,
	GET_ALPHA
}	t_action;

typedef enum e_minimap
{
	MAP_FLOOR = 48,
	MAP_WALL = 49,
	MAP_OPENED = 79,
	MAP_CLOSED = 67,
}	t_minimap;

typedef enum e_image
{
	IMG_NO,
	IMG_SO,
	IMG_WE,
	IMG_EA,
	IMG_DR,
	IMG_FL,
	IMG_RF
}	t_image;

typedef enum e_color
{
	COL_F,
	COL_C
}	t_color;

typedef enum e_status
{
	STAT_OPEN,
	STAT_CLOSE
}	t_status;

typedef enum e_animation
{
	IMG_MP,
	IMG_PS,
	IMG_W1,
	IMG_W2,
	IMG_TO,
	IMG_T1,
	IMG_T2,
	IMG_T3,
	IMG_T4,
	IMG_T5
}	t_animation;

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
	int32_t		mouse[2];
	bool		status[GAME_STATS];
	int32_t		color[GAME_COLORS];
	mlx_image_t	*image[GAME_ASSETS];
	mlx_image_t	*anim[GAME_ANIMS];
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
void	load_assets(t_cubed *game);

//		Hook
void	hook_movement(void *param);
void	move_camera(t_cubed *game, t_action action);
void	rotate_camera(t_cubed *game, t_action action);
void	hook_actions(mlx_key_data_t keydata, void *param);
void	open_door(t_cubed *game);
void	close_door(t_cubed *game);
void	hook_mouse(void *param);
void	draw_scene(void *param);
void	hook_close(void *param);
void	get_position(int *target, int x, int y);
void	set_buffer(int *buffer, int size, t_cubed *game);

//		Draw
void	draw_walls(t_cubed *game);
void	draw_segment(int x, int height, t_vector *ray, t_cubed *game);
void	draw_background(int start, int end, int x, t_cubed *game);
void	draw_minimap(t_cubed *game);
void	animate_minimap(t_cubed *game);
void	animate_shotgun(t_cubed *game);
void	wait_frame(t_cubed *game, float limit);
void	draw_shotgun(t_cubed *game);
void	calculate_ray(t_vector *ray, t_cubed *game);
void	calculate_draw(int *height, t_vector *ray, t_cubed *game);
void	ft_putpixel(int x, int y, int32_t color, t_cubed *game);
int32_t	get_color(mlx_image_t *img, uint32_t x, uint32_t y);
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
char	**safe_split(char * str, char c, t_cubed *game);

//		Safe
void	*safe_calloc(size_t n, t_cubed *game);
void	safe_draw(mlx_image_t *img, int x, int y, t_cubed *game);
void	*safe_tex(char *file, bool allocated, t_cubed *game);
void	*safe_img(uint32_t w, uint32_t h, mlx_texture_t *t, t_cubed *game);

#endif
