/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_asset_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:48:53 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/30 11:48:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	free_assets(t_cubed *game)
{
	int	i;

	i = 0;
	while (i < GAME_ASSETS)
	{
		if (game->asset[i] != NULL)
			mlx_delete_image(game->mlx, game->asset[i]);
		i++;
	}
}

void	free_sprites(t_cubed *game)
{
	t_sprite	*sprite;
	int			i;
	int			j;

	i = 0;
	while (i < GAME_SPRITES)
	{
		j = 0;
		sprite = game->sprite[i];
		while (j < sprite->frame_count)
		{
			mlx_delete_image(game->mlx, sprite->frame[j]);
			j++;
		}
		free(sprite->frame);
		free(sprite);
		sprite = NULL;
		i++;
	}
}
