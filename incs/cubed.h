/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/11 19:03:43 by jmertane         ###   ########.fr       */
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
# define STEP_ANGLE 0.1
# define STEP_MOVE 8
# define BPP sizeof(int)

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	fov;
}	t_player;

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
	t_vector	vec;
	float		scale;
	void		*tex;
	void		*img;
	int			fd;
}	t_texture;

typedef struct s_cubed
{
	t_player	player;
	t_mapinfo	map;
	t_texture	*texture;
	void		*mlx;
}	t_cubed;

#endif
