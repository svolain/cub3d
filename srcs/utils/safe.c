/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:46:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/26 22:34:07 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

mlx_image_t	*safe_image(uint32_t w, uint32_t h ,mlx_texture_t *t, t_cubed *game)
{
	mlx_image_t	*i;

	if (!t)
		i = mlx_new_image(game->mlx, w, h);
	else
		i = mlx_texture_to_image(game->mlx, t);
	if (!i)
	{
		if (t != NULL)
			mlx_delete_texture(t);
		error_exit(ERR_MLX, MSG_MLX, game);
	}
	return (i);
}

mlx_texture_t	*safe_texture(char * file, t_cubed *game)
{
	mlx_texture_t	*t;

	t = mlx_load_png(file);
	if (!t)
	{
		free_single(&file);
		error_exit(ERR_MLX, MSG_MLX, game);
	}
	return (t);
}

char	*safe_strjoin(char *s1, char *s2, t_cubed *game)
{
	char	*s;

	s = ft_strjoin(s1, s2);
	if (!s)
		error_fatal(ENOMEM, MSG_MEM, game);
	return (s);
}

char	**safe_split(char *str, char c, t_cubed *game)
{
	char	**s;

	s = ft_split(str, c);
	if (!s)
		error_fatal(ENOMEM, MSG_MEM, game);
	return (s);
}

char	*safe_substr(char *stt, char *end, t_cubed *game)
{
	char	*s;

	s = ft_substr(stt, 0, end - stt);
	if (!s)
		error_fatal(ENOMEM, MSG_MEM, game);
	return (s);
}

void	*safe_calloc(size_t n, t_cubed *game)
{
	void	*p;

	p = ft_calloc(1, n);
	if (!p)
		error_fatal(ENOMEM, MSG_MEM, game);
	return (p);
}
