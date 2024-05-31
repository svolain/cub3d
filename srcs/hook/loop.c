
#include <cubed.h>

static void	wait_frame(t_cubed *game)
{
	static double	frame = 0;

	while (frame < game->fps)
		frame += game->mlx->delta_time;
	game->fps += FPS;
}

void	draw_scene(void *param)
{
	t_cubed	*game;

	game = param;
	wait_frame(game);
	draw_minimap(game);
	draw_walls(game);
}
