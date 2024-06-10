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

# define GAME_ASSETS 7
# define GAME_COLORS 2
# define GAME_ANIMS 20
# define GAME_STATS 2

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define SCREEN_TITLE "cub3d"

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

# define TEX_GUN1		"./textures/gun/gun_idle.png"
# define TEX_GUN2		"./textures/gun/gun_shoot1.png"
# define TEX_GUN3		"./textures/gun/gun_shoot2.png"
# define TEX_GUN4		"./textures/gun/gun_shoot3.png"
# define TEX_GUN5		"./textures/gun/gun_shoot4.png"
# define TEX_GUN6		"./textures/gun/gun_reload1.png"
# define TEX_GUN7		"./textures/gun/gun_reload2.png"
# define TEX_GUN8		"./textures/gun/gun_reload3.png"
# define TEX_GUN9		"./textures/gun/gun_reload4.png"
# define TEX_GUN10		"./textures/gun/gun_reload5.png"
# define TEX_GUN11		"./textures/gun/gun_reload6.png"
# define TEX_GUN12		"./textures/gun/gun_reload7.png"
# define TEX_GUN13		"./textures/gun/gun_reload8.png"
# define TEX_GUN14		"./textures/gun/gun_reload9.png"
# define TEX_GUN15		"./textures/gun/gun_reload10.png"

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
	G = 2,
	R = 3
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
	IMG_GO,
	IMG_G1,
	IMG_G2,
	IMG_G3,
	IMG_G4,
	IMG_G5,
	IMG_G6,
	IMG_G7,
	IMG_G8,
	IMG_G9,
	IMG_G10,
	IMG_G11,
	IMG_G12,
	IMG_G13,
	IMG_G14,
	IMG_G15
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

typedef struct s_rgba
{
	uint32_t	color;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
}	t_rgba;

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
void	hook_action(mlx_key_data_t keydata, void *param);
void	hook_mouse(void *param);
void	hook_close(void *param);
void	move_camera(t_cubed *game, t_action action);
void	rotate_camera(t_cubed *game, t_action action);
void	get_map_position(int *target, int x, int y);
void	set_buffer(int *buffer, int size, t_cubed *game);

//		Render
void	render_scenario(void *param);
void	render_worldspace(t_cubed *game);
void	render_background(t_cubed *game);
void	render_minimap(t_cubed *game);

//		Calc
void	calculate_ray(t_vector *ray, t_cubed *game);

int32_t	get_channel_color(int32_t rgba, t_action action);
int32_t	get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
int32_t	get_alpha_blend(int32_t source, int32_t current);
int32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void	image_to_canvas(int dst_x, int dst_y, mlx_image_t *img, t_cubed *game);
void	ft_put_pixel(int x, int y, int32_t color, t_cubed *game);

//		Anim
void	animate_minimap(t_cubed *game);
void	animate_shotgun(t_cubed *game, int i);
void	wait_frame(t_cubed *game, float limit);
void	calculate_ray(t_vector *ray, t_cubed *game);
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
