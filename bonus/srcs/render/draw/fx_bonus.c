
#include <cubed_bonus.h>

static void	transparent_void(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * BPP);
}

static int32_t	calculate_blend(int screen[2])
{
	/* int	alpha; */
	/**/
	/* if (screen[X] > 255 && screen[X] < SCREEN_WIDTH - 255) */
	/* 	screen[X] = 255; */
	/* else if (screen[X] > SCREEN_WIDTH - 255) */
	/* 	screen[X] = SCREEN_WIDTH - screen[X]; */
	/* if (screen[Y] > 255 && screen[Y] < SCREEN_HEIGHT - 255) */
	/* 	screen[Y] = 255; */
	/* else if (screen[Y] > SCREEN_HEIGHT - 255) */
	/* 	screen[Y] = SCREEN_HEIGHT - screen[Y]; */
	/* alpha = 255 - ((screen[X] + screen[Y]) / 2); */
	/* printf("alpha = %d | screen_x = %d | screen_y = %d\n", alpha, screen[X], screen[Y]); */
	/* return (get_rgba(255, 255, 255, alpha)); */
	(void)screen;
	return COLOR_PICKUP;
}

void	draw_screen_fx(int32_t course, t_cubed *game)
{
	int		screen[2];
	int32_t	shade;
	int32_t	color;

	screen[X] = 0;
	safe_mutex(&game->mtx[MTX_FX], MTX_LOCK, game);
	while (screen[X] < SCREEN_WIDTH)
	{
		screen[Y] = 0;
		while (screen[Y] < SCREEN_HEIGHT)
		{
			shade = calculate_blend(screen);
			color = get_alpha_blend(shade, course);
			ft_put_pixel(screen[X], screen[Y], color, game->asset[IMG_FX]);
			screen[Y]++;
		}
		screen[X]++;
	}
	wait_frame(game, 5000);
	transparent_void(game->asset[IMG_FX]);
	safe_mutex(&game->mtx[MTX_FX], MTX_UNLOCK, game);
}
