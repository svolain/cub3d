/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:04:40 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/25 20:06:09 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	error_occured(char *file, mlx_texture_t *texture, t_cubed *game)
{
	if (file != NULL)
		free_single(&file);
	if (texture != NULL)
		mlx_delete_texture(texture);
	error_exit(ERR_MLX, MSG_MLX, game);
}

void	load_color(void)
{
	printf("loaded an color!\n");
}

void	load_sprite(t_element index, char *start, bool *loaded, t_cubed *game)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	char			*file;
	char			*end;

	while (*start && *start == ' ')
		start++;
	if (!*start || *start == '\n')
		error_exit(ERR_ELEM, MSG_ELEM, game);
	end = ft_strchr(start, '\n');
	file = safe_substr(start, end, game);
	texture = mlx_load_png(file);
	if (!texture)
		error_occured(file, texture, game);
	image = game->img + index;
	image = mlx_texture_to_image(game->mlx, texture);
	if (!image)
		error_occured(file, texture, game);
	mlx_delete_texture(texture);
	free_single(&file);
	*loaded = true;
}

void	load_image(void)
{
	printf("loaded an image!\n");
}
