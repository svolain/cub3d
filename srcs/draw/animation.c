/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:06:35 by vsavolai          #+#    #+#             */
/*   Updated: 2024/06/04 15:53:43 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	animate_minimap(t_cubed *game)
{
	static int	i;
	mlx_image_t	*old;
	mlx_image_t	*new;

	old = game->minimap_player[IMG_MP];
	i++;
	if (i > 3)
		i = 0;
	new = game->minimap_player[i];
	ft_memcpy(old->pixels, new->pixels,
			old->height * old->width * sizeof(int32_t));
}

void	animate_torch(t_cubed *game)
{
	static int	i;
	mlx_image_t	*old;
	mlx_image_t	*new;

	old = game->torch[IMG_TO];
	i++;
	if (i > 5)
		i = 0;
	new = game->torch[i];
	ft_memcpy(old->pixels, new->pixels,
			old->height * old->width * sizeof(int32_t));
}

void	draw_torch(t_cubed *game)
{
	int x;
	int y;

	x = SCREEN_WIDTH / 2 - 100;
	y = SCREEN_HEIGHT - 330;
	safe_draw(game->torch[IMG_TO], x, y, game);
}

void	load_animation(t_cubed *game)
{
	game->minimap_player[IMG_W1] = safe_image(0, 0, safe_texture(TEX_PLAYER_WALK1, false, game), game);
	game->minimap_player[IMG_W2] =
		safe_image(0, 0, safe_texture(TEX_PLAYER_WALK2, false, game), game);
	game->minimap_player[IMG_PS] =
		safe_image(0, 0, safe_texture(TEX_MINI_PLAYER, false, game), game);
	game->minimap_player[IMG_MP] = game->minimap_player[IMG_PS];
	game->torch[IMG_T1] =
		safe_image(0, 0, safe_texture(TEX_TORCH1, false, game), game);
	game->torch[IMG_T2] =
		safe_image(0, 0, safe_texture(TEX_TORCH2, false, game), game);
	game->torch[IMG_T3] =
		safe_image(0, 0, safe_texture(TEX_TORCH3, false, game), game);
	game->torch[IMG_T4] =
		safe_image(0, 0, safe_texture(TEX_TORCH4, false, game), game);
	game->torch[IMG_T5] =
		safe_image(0, 0, safe_texture(TEX_TORCH5, false, game), game);
	game->torch[IMG_T6] =
		safe_image(0, 0, safe_texture(TEX_TORCH6, false, game), game);	
	game->torch[IMG_TO] = game->torch[IMG_T1];
}
