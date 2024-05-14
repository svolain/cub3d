/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/12 20:23:30 by jmertane         ###   ########.fr       */
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

# define PI 3.1415926535898
# define DEGREE PI / 360

# define EAST 0
# define NORTH PI / 2
# define WEST PI
# define SOUTH 3 * PI / 2

# define STEP_ANGLE 0.1
# define STEP_MOVE 8
# define BPP sizeof(int)

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

typedef struct s_camera
{
	float	x;
	float	y;
	float	angle;
	float	fov;
	int		dof;
}	t_camera;

typedef struct s_vector
{
	float	x;
	float	y;
	float	angle;
}	t_vector;

typedef struct s_mapinfo
{
	char	**matrix;
	int		width;
	int		height;
}	t_mapinfo;

typedef struct s_texture
{
	t_vector			vec;
	float				scale;
	void				*tex;
	void				*img;
	int					fd;
	struct s_texture	*next;
}	t_texture;

typedef struct s_cubed
{
	t_camera	cam;
	t_mapinfo	map;
	t_texture	*tex;
	void		*mlx;
}	t_cubed;

#endif
