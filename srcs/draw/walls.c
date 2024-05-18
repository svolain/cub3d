#include <cubed.h>

void	draw_walls(t_cubed *game, t_vector *vec)
{
	float	height;

	height = CELLSIZE * SCREEN_HEIGHT / vec->dist;
	if (height > SCREEN_HEIGHT)
		height = SCREEN_HEIGHT;
}
