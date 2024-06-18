/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/18 14:57:59 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <MLX42.h>
# include <libft.h>
# include <error.h>
# include <asset.h>
# include <multi.h>

# include <pthread.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define SCREEN_TITLE "cub3d"

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

# define CELLSIZE 256
# define BUMP_BUFFER CELLSIZE / 2
# define ANGLE_MODIFIER 0.0002f
# define MOVE_MODIFIER 16.0f

# define STEP_ANGLE CELLSIZE * ANGLE_MODIFIER
# define STEP_MOVEMENT CELLSIZE / MOVE_MODIFIER
# define STEP_WINDOW FOV / SCREEN_WIDTH

# define MAPLIMIT 500
# define MAPSCALE 8
# define MAPGRID 10
# define MAPBORDER 5

# define MAPCELL (CELLSIZE / MAPSCALE)
# define MAPSIZE (MAPCELL * MAPGRID)
# define MAPCENTER (MAPSIZE / 2) - (MAPCELL / 2)

# define BPP sizeof(int32_t)

# define TRANSPARENT	get_rgba(0, 0, 0, 0)
# define COLOR_BORDER	get_rgba(50, 100, 200, 100)
# define COLOR_RAY		get_rgba(225, 100, 100, 150)
# define COLOR_GRID		get_rgba(50, 50, 50, 200)
# define COLOR_WALL		get_rgba(150, 150, 150, 150)
# define COLOR_FLOOR	get_rgba(215, 255, 255, 200)
# define COLOR_DOOR_O	get_rgba(100, 200, 50, 255)
# define COLOR_DOOR_C	get_rgba(50, 150, 150, 255)

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
	DOOR_OPEN,
	DOOR_CLOSE,
	GET_RED,
	GET_GREEN,
	GET_BLUE,
	GET_ALPHA,
}	t_action;

typedef enum e_minimap
{
	MAP_FLOOR = 48,
	MAP_WALL = 49,
	MAP_OPENED = 79,
	MAP_CLOSED = 67,
}	t_minimap;

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

typedef struct s_anim
{
	int			active;
	int			current_frame;
	int			frame_count;
	double		timer;
	double		delay;
}	t_anim;

typedef struct s_cubed
{
	t_camera	*cam;
	t_mapinfo	*map;
	char		*gnl;
	mlx_t		*mlx;
	t_anim		*animation;
	int32_t		mouse[2];
	int32_t		color[GAME_COLORS];
	mlx_image_t	*image[GAME_ASSETS];
	mlx_image_t	*anim[GAME_ANIMS];
	pthread_t	tid[GAME_THREADS];
	t_mtx		mtx[GAME_MUTEXES];
	bool		status[GAME_STATS];
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
void	hook_click(void *param);
void	hook_close(void *param);
void	hook_animation(void *param);

//		Move
void	move_camera(t_cubed *game, t_action action);

//		Rotate
void	rotate_camera(t_cubed *game, t_action action);
void	ft_rotate(float *target, float angle, t_action action);
void	fix_fisheye(t_vector *ray, float angle);
float	ft_degtorad(float degree);

//		Render
void	*render_walls(void *param);
void	*render_floor(void *param);
void	*render_minimap(void *param);
void	*render_fov(void *param);

//		Draw
void	draw_walls(t_camera *cam, float angle, t_cubed *game);
void	draw_floor(t_camera *cam, float angle, t_cubed *game);
void	draw_minimap(int cam_x, int cam_y, t_cubed *game);
void	draw_fov(t_camera *cam, float angle, t_cubed *game);

//		Animate
void	animate_shotgun(t_cubed *game);
void	wait_frame(t_cubed *game, float limit);
void	draw_shotgun(t_cubed *game);
void	init_animation(t_cubed *game);

//		Calculate
void	calculate_ray(t_vector *ray, t_camera *cam, t_cubed *game);

//		Colors
int32_t	get_channel_color(int32_t rgba, t_action action);
int32_t	get_alpha_blend(int32_t source, int32_t current);
int32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

//		Pixels
int32_t	get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
void	ft_put_pixel(int x, int y, int32_t color, mlx_image_t *img);

//		Error
void	error_log(char *msg1, char *msg2, char *msg3);
void	error_exit(int errcode, char *errmsg, t_cubed *game);
void	error_fatal(int errcode, char *errmsg, t_cubed *game);

//		Free
void	free_exit(t_cubed *game, int excode);
void	free_double(char ***str);
void	free_single(char **str);

//		String
char	*safe_substr(char *stt, char *end, t_cubed *game);
char	*safe_strjoin(char *s1, char *s2, t_cubed *game);
char	**safe_split(char * str, char c, t_cubed *game);

//		Safe
void	*safe_calloc(size_t n, t_cubed *game);
void	safe_draw(mlx_image_t *img, int x, int y, t_cubed *game);
void	*safe_tex(char *file, bool allocated, t_cubed *game);
void	*safe_img(uint32_t w, uint32_t h, mlx_texture_t *t, t_cubed *game);

//		Threads
void	safe_thread(pthread_t *tid, t_operation action, t_cubed *game);
void	safe_mutex(t_mtx *mutex, t_operation action, t_cubed *game);
void	get_map_position(int target[2], int x, int y);
char	get_map_element(int x, int y, t_cubed *game);
void	set_map_element(int x, int y, char c, t_cubed *game);
void	get_camera(t_camera *cam, t_cubed *game);
void	set_camera(t_camera *cam, t_cubed *game);
bool	get_bool(bool *val, t_mtx *mutex, t_cubed *game);
void	set_bool(bool *dst, bool val, t_mtx *mutex, t_cubed *game);
void	set_finished(t_cubed *game);
bool	game_over(t_cubed *game);

#endif
