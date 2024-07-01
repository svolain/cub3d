/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/30 11:54:45 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_BONUS_H
# define CUBED_BONUS_H

# include <MLX42.h>
# include <libft.h>

# include <error_bonus.h>
# include <asset_bonus.h>
# include <multi_bonus.h>

# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define SCREEN_TITLE "cub3d"

# define CHARSET_ALLOWED	"01COHAXNSEW "
# define CHARSET_PLAYER		"NSEW"
# define CHARSET_MOVEABLE	"0OHAX"
# define CHARSET_WALL		"C1"
# define CHARSET_SPRITE		"HAX"

# define PI 3.1415926535898f
# define FRAME_LIMIT 500
# define FRAME_DELAY 0.002f

# define EAST 0
# define NORTH PI / 2.0f
# define WEST PI
# define SOUTH 3.0f * PI / 2.0f

# define FOV_IN_DEGREE 60
# define FOV ft_degtorad(FOV_IN_DEGREE)
# define DEGREE ft_degtorad(1)

# define CELLSIZE 256
# define BUMP_BUFFER (CELLSIZE / 2)
# define ANGLE_MODIFIER 0.00033f
# define MOVE_MODIFIER 0.1155f

# define STEP_ANGLE (CELLSIZE * ANGLE_MODIFIER)
# define STEP_MOVEMENT (CELLSIZE * MOVE_MODIFIER)
# define STEP_WINDOW (FOV / SCREEN_WIDTH)

# define MAPLIMIT 500
# define MAPSCALE 8
# define MAPGRID 10
# define MAPBORDER 5

# define MAPCELL (CELLSIZE / MAPSCALE)
# define MAPSIZE (MAPCELL * MAPGRID)
# define MAPCENTER ((MAPSIZE / 2) - (MAPCELL / 2))

# define HUD_HEIGHT SCREEN_HEIGHT / 8
# define HUD_MIDDLE SCREEN_HEIGHT - 150

# define BPP sizeof(int32_t)

# define TRANSPARENT	get_rgba(0, 0, 0, 0)
# define COLOR_BLACK	get_rgba(0, 0, 0, 255)

# define COLOR_BORDER	get_rgba(50, 100, 200, 200)
# define COLOR_GRID		get_rgba(50, 50, 50, 200)
# define COLOR_WALL		get_rgba(150, 150, 150, 200)
# define COLOR_FLOOR	get_rgba(215, 255, 255, 200)
# define COLOR_DOOR_O	get_rgba(100, 200, 50, 200)
# define COLOR_DOOR_C	get_rgba(50, 150, 150, 200)
# define COLOR_PICKUP	get_rgba(125, 155, 75, 155)
# define COLOR_HUD		get_rgba(50, 100, 200, 200)

typedef enum e_check
{
	FAILURE = -1,
	SUCCESS = 0,
	X = 0,
	Y = 1,
	V = 0,
	H = 1,
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
	MAP_NORTH = 78,
	MAP_SOUTH = 83,
	MAP_EAST = 69,
	MAP_WEST = 87,
	MAP_FLOOR = 48,
	MAP_WALL = 49,
	MAP_OPENED = 79,
	MAP_CLOSED = 67,
	MAP_HEALTH = 72,
	MAP_AMMO = 65,
	MAP_EXIT = 88,
}	t_minimap;

typedef struct s_rgba
{
	uint32_t	color;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
}	t_rgba;

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
	float		z;
	float		a;
	float		dx;
	float		dy;
}	t_camera;

typedef struct s_player
{
	char		*health;
	char		*ammo;
	mlx_image_t	*img[2];
}	t_player;

typedef struct s_sprite
{
	bool		status[2];
	int			current_frame;
	int			frame_count;
	mlx_image_t	**frame;
	double		timer;
	double		delay;
}	t_sprite;

typedef struct s_sprinfo
{
	float		x;
	float		y;
	float		z;
	float		dx;
	float		dy;
	mlx_image_t	*img;
}	t_sprinfo;

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
	t_player	*plr;
	t_mapinfo	*map;
	char		*gnl;
	mlx_t		*mlx;
	int32_t		mouse[2];
	int32_t		color[GAME_COLORS];
	mlx_image_t	*asset[GAME_ASSETS];
	t_sprite	*sprite[GAME_SPRITES];
	t_mtx		mtx[GAME_MUTEXES];
	pthread_t	tid[GAME_THREADS];
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
void	load_texture(t_image index, char *start, bool *loaded, t_cubed *game);
void	load_color(t_color index, char *start, bool *loaded, t_cubed *game);
void	init_sprite(int index, int frame_count, double delay, t_cubed *game);
void	load_custom_assets(t_cubed *game);
void	load_weapon_frames(t_sprite *spr, t_cubed *game);
void	load_portal_frames(t_sprite *spr, t_cubed *game);

//		Hook
void	hook_movement(void *param);
void	hook_action(mlx_key_data_t keydata, void *param);
void	hook_mouse(void *param);
void	hook_click(void *param);
void	hook_close(void *param);
void	hook_weapon(void *param);

//		Camera
void	move_camera(t_cubed *game, t_action action);
void	rotate_camera(t_cubed *game, t_action action);
void	ft_rotate(float *target, float angle, t_action action);
void	fix_fisheye(t_vector *ray, float angle);
float	ft_degtorad(float degree);

//		Gameplay
void	init_player_info(t_cubed *game);

//		Render
void	*render_walls(void *param);
void	*render_floor(void *param);
void	*render_sprites(void *param);
void	*render_minimap(void *param);
void	*render_fov(void *param);
void	*render_hud(void *param);

//		Draw
void	draw_walls(t_camera *cam, float angle, t_cubed *game);
void	draw_floor(t_camera *cam, float angle, t_cubed *game);
void	draw_sprites(t_camera *cam, t_cubed *game);
void	draw_minimap(int cam_x, int cam_y, t_cubed *game);
void	draw_fov(t_camera *cam, float angle, t_cubed *game);
void	draw_hud(t_cubed *game);
void	draw_screen_fx(int32_t course, t_cubed *game);

//		Weapon
void	draw_weapon_frames(t_sprite *spr, t_cubed *game);
void	weapon_shoot(t_sprite *spr, t_cubed *game);
void	weapon_move(t_sprite *spr, t_cubed	*game);

//		Animation
void	wait_frame(t_cubed *game, float ms_limit);
void	loop_portal(t_sprite *spr, t_cubed *game);

//		Calculate
void	calculate_ray(t_vector *ray, t_camera *cam, t_cubed *game);
void	calculate_wall(int *height, t_vector *ray, t_cubed *game);
void	calc_spr_walls(float *depth, t_camera *cam, t_cubed *game);
void	calc_spr_scr(int map[2], t_sprinfo *spr, t_camera *cam);
void	calc_spr_tex(int map[2], t_sprinfo *spr, t_sprinfo *tex, t_cubed *game);

//		Draw utils
int32_t	get_channel_color(int32_t rgba, t_action action);
int32_t	get_alpha_blend(int32_t source, int32_t current);
int32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int32_t	get_pixel_color(mlx_image_t *img, uint32_t x, uint32_t y);
int		ft_valid_pixel(mlx_image_t *img, uint32_t x, uint32_t y);
void	ft_put_pixel(int x, int y, int32_t color, mlx_image_t *img);

//		Map utils
int		ft_is_grid(int x, int y);
int		ft_is_border(int x, int y);
bool	ft_inside_map(int x, int y, t_cubed *game);
char	ft_in_elements(int x, int y, char *set, t_cubed *game);
char	ft_in_sprite(int map[2], t_camera *cam, t_cubed *game);

//		Error
void	error_log(char *msg1, char *msg2, char *msg3);
void	error_exit(int errcode, char *errmsg, t_cubed *game);
void	error_fatal(int errcode, char *errmsg, t_cubed *game);

//		Free
void	free_exit(t_cubed *game, int excode);
void	free_assets(t_cubed *game);
void	free_sprites(t_cubed *game);
void	join_threads(t_cubed *game);
void	destroy_mutexes(t_cubed *game);
void	free_double(char ***str);
void	free_single(char **str);

//		Safe
char	*safe_itoa(int value, t_cubed *game);
char	*safe_substr(char *stt, char *end, t_cubed *game);
char	*safe_strjoin(char *s1, char *s2, t_cubed *game);
char	**safe_split(char *str, char c, t_cubed *game);
void	*safe_calloc(size_t n, t_cubed *game);
void	*safe_tex(char *file, bool allocated, t_cubed *game);
void	*safe_img(uint32_t w, uint32_t h, mlx_texture_t *t, t_cubed *game);
void	safe_draw(mlx_image_t *img, int x, int y, t_cubed *game);
void	safe_resize(mlx_image_t *img, int x, int y, t_cubed *game);
void	safe_thread(pthread_t *tid, t_operation action, t_cubed *game);
void	safe_mutex(t_mtx *mutex, t_operation action, t_cubed *game);

//		Getset
void	get_map_position(int target[2], int x, int y);
char	get_map_element(int x, int y, t_cubed *game);
void	set_map_element(int x, int y, char c, t_cubed *game);
void	get_camera(t_camera *cam, t_cubed *game);
void	set_camera(t_camera *cam, t_cubed *game);
char	*get_player_str(char **str, t_cubed *game);
void	set_player_value(char **str, int value, t_cubed *game);
int		get_player_value(char *str, t_cubed *game);
void	*get_portal_frame(t_sprite *spr, t_cubed *game);
void	set_status(bool *dst, bool val, t_mtx *mutex, t_cubed *game);
bool	get_status(bool *val, t_mtx *mutex, t_cubed *game);
void	set_game_over(t_cubed *game);
bool	game_over(t_cubed *game);

#endif
