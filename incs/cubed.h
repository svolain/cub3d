/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/15 08:20:32 by jmertane         ###   ########.fr       */
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

# define FOV PI / 4

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

typedef enum e_elements
{
	FLOOR = 48,
	WALL
}	t_elements;

typedef struct s_cam
{
	float	x;
	float	y;
	float	a;
}	t_cam;

typedef struct s_vec
{
	float	x;
	float	y;
	float	a;
}	t_vec;

typedef struct s_map
{
	char	**map;
	char	*file;
	int		width;
	int		height;
	int		fd;
}	t_map;

typedef struct s_tex
{
	t_vec			vec;
	float			scale;
	void			*tex;
	void			*img;
	int				fd;
	struct s_tex	*next;
}	t_tex;

typedef struct s_cubed
{
	t_cam		*cam;
	t_map		*map;
	t_tex		*tex;
	void		*mlx;
}	t_cubed;

//		Initialization
void	init_game(t_cubed *game, char *file);

//		Calculations
void	calculate_rays(t_cubed *game);

//		Error handling
void	free_exit(t_cubed *game);
void	error_exit(int errcode, char *errmsg, t_cubed *game);
void	error_fatal(int errcode, char *errmsg, t_cubed *game);

//		Safety wrappers
char	*safe_strjoin(char *s1, char *s2, char **buf, t_cubed *game);
void	*safe_calloc(size_t n, t_cubed *game);

#endif
