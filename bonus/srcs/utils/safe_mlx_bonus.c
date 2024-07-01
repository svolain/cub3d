/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:46:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/05 20:07:04 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	safe_draw(mlx_image_t *img, int x, int y, t_cubed *game)
{
	if (mlx_image_to_window(game->mlx, img, x, y) == FAILURE)
		error_exit(ERR_MLX, MSG_MLX, game);
}

void	safe_resize(mlx_image_t *img, int x, int y, t_cubed *game)
{
	if (mlx_resize_image(img, x, y) == false)
		error_exit(ERR_MLX, MSG_MLX, game);
}

void	*safe_img(uint32_t w, uint32_t h, mlx_texture_t *t, t_cubed *game)
{
	mlx_image_t	*i;

	if (!t)
		i = mlx_new_image(game->mlx, w, h);
	else
		i = mlx_texture_to_image(game->mlx, t);
	if (t != NULL)
		mlx_delete_texture(t);
	if (!i)
		error_exit(ERR_MLX, MSG_MLX, game);
	return (i);
}

void	*safe_tex(char *file, bool allocated, t_cubed *game)
{
	mlx_texture_t	*t;

	t = mlx_load_png(file);
	if (!t)
	{
		if (allocated)
			free_single(&file);
		error_exit(ERR_MLX, MSG_MLX, game);
	}
	return (t);
}

void	*safe_calloc(size_t n, t_cubed *game)
{
	void	*p;

	p = ft_calloc(1, n);
	if (!p)
		error_fatal(ENOMEM, MSG_MEM, game);
	return (p);
}
