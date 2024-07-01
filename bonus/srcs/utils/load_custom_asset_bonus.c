/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:38:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/28 13:01:37 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static void	set_image_color(mlx_image_t *img, int32_t color)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height)
		{
			ft_put_pixel(i, j, color, img);
			j++;
		}
		i++;
	}
}

void	load_custom_assets(t_cubed *game)
{
	game->asset[IMG_BG] = safe_img(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, game);
	game->asset[IMG_FG] = safe_img(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, game);
	game->asset[IMG_OL] = safe_img(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, game);
	game->asset[IMG_FX] = safe_img(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, game);
	game->asset[IMG_MM] = safe_img(MAPSIZE, MAPSIZE, NULL, game);
	game->asset[IMG_FV] = safe_img(MAPSIZE, MAPSIZE, NULL, game);
	game->asset[IMG_FL] = safe_img(0, 0, safe_tex(TEX_FLOOR, 0, game), game);
	game->asset[IMG_RF] = safe_img(0, 0, safe_tex(TEX_ROOF, 0, game), game);
	game->asset[IMG_DR] = safe_img(0, 0, safe_tex(TEX_DOOR, 0, game), game);
	game->asset[IMG_PL] = safe_img(0, 0, safe_tex(TEX_PLAYER, 0, game), game);
	game->asset[IMG_HL] = safe_img(0, 0, safe_tex(TEX_HEALTH, 0, game), game);
	game->asset[IMG_AM] = safe_img(0, 0, safe_tex(TEX_AMMO, 0, game), game);
	game->asset[IMG_HD] = safe_img(SCREEN_WIDTH, HUD_HEIGHT, NULL, game);
	set_image_color(game->asset[IMG_BG], COLOR_BLACK);
	set_image_color(game->asset[IMG_FG], COLOR_BLACK);
	set_image_color(game->asset[IMG_OL], TRANSPARENT);
	set_image_color(game->asset[IMG_FX], COLOR_PICKUP);
	set_image_color(game->asset[IMG_HD], COLOR_HUD);
	game->asset[IMG_FX]->enabled = false;
}

void	load_weapon_frames(t_sprite *spr, t_cubed *game)
{
	spr->frame[IMG_BASE] = safe_img(0, 0, safe_tex(TEX_GUN1, 0, game), game);
	spr->frame[IMG_W1] = safe_img(0, 0, safe_tex(TEX_GUN1, 0, game), game);
	spr->frame[IMG_W2] = safe_img(0, 0, safe_tex(TEX_GUN2, 0, game), game);
	spr->frame[IMG_W3] = safe_img(0, 0, safe_tex(TEX_GUN3, 0, game), game);
	spr->frame[IMG_W4] = safe_img(0, 0, safe_tex(TEX_GUN4, 0, game), game);
	spr->frame[IMG_W5] = safe_img(0, 0, safe_tex(TEX_GUN5, 0, game), game);
	spr->frame[IMG_W6] = safe_img(0, 0, safe_tex(TEX_GUN6, 0, game), game);
	spr->frame[IMG_W7] = safe_img(0, 0, safe_tex(TEX_GUN7, 0, game), game);
	spr->frame[IMG_W8] = safe_img(0, 0, safe_tex(TEX_GUN8, 0, game), game);
	spr->frame[IMG_W9] = safe_img(0, 0, safe_tex(TEX_GUN9, 0, game), game);
	spr->frame[IMG_W10] = safe_img(0, 0, safe_tex(TEX_GUN10, 0, game), game);
	spr->frame[IMG_W11] = safe_img(0, 0, safe_tex(TEX_GUN11, 0, game), game);
	spr->frame[IMG_W12] = safe_img(0, 0, safe_tex(TEX_GUN12, 0, game), game);
	spr->frame[IMG_W13] = safe_img(0, 0, safe_tex(TEX_GUN13, 0, game), game);
	spr->frame[IMG_W14] = safe_img(0, 0, safe_tex(TEX_GUN14, 0, game), game);
	spr->frame[IMG_W15] = safe_img(0, 0, safe_tex(TEX_GUN15, 0, game), game);
}

void	load_portal_frames(t_sprite *spr, t_cubed *game)
{
	spr->frame[IMG_BASE] = safe_img(0, 0, safe_tex(TEX_GATE1, 0, game), game);
	spr->frame[IMG_P1] = safe_img(0, 0, safe_tex(TEX_GATE1, 0, game), game);
	spr->frame[IMG_P2] = safe_img(0, 0, safe_tex(TEX_GATE2, 0, game), game);
	spr->frame[IMG_P3] = safe_img(0, 0, safe_tex(TEX_GATE3, 0, game), game);
	spr->frame[IMG_P4] = safe_img(0, 0, safe_tex(TEX_GATE4, 0, game), game);
	spr->frame[IMG_P5] = safe_img(0, 0, safe_tex(TEX_GATE5, 0, game), game);
	spr->frame[IMG_P6] = safe_img(0, 0, safe_tex(TEX_GATE6, 0, game), game);
	spr->frame[IMG_P7] = safe_img(0, 0, safe_tex(TEX_GATE7, 0, game), game);
}
