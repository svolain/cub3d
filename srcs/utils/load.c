/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:04:40 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/05 20:05:37 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	error_occured(char *str, char **arr, t_cubed *game)
{
	if (str != NULL)
		free_single(&str);
	if (arr != NULL)
		free_double(&arr);
	error_exit(ERR_ELEM, MSG_ELEM, game);
}

static int32_t	parse_color(char *color, int iteration)
{
	int	i;

	i = 0;
	if (!color || iteration > 2)
		return (FAILURE);
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (FAILURE);
		i++;
	}
	if (ft_strlen(color) > 3
		|| ft_atoi(color) > 255)
		return (FAILURE);
	return (ft_atoi(color));
}

void	load_color(t_color index, char *start, bool *loaded, t_cubed *game)
{
	int32_t	rgba[4];
	char	**colors;
	char	*values;
	char	*end;
	int		i;

	start = ft_skipspaces(start, game);
	end = ft_strrchr(start, '\n');
	values = safe_substr(start, end, game);
	colors = safe_split(values, ',', game);
	i = 0;
	while (colors[i])
	{
		rgba[i] = parse_color(colors[i], i);
		if (rgba[i] == FAILURE)
			error_occured(values, colors, game);
		i++;
	}
	game->color[index] = get_rgba(rgba[0], rgba[1], rgba[2], 255);
	free_double(&colors);
	free_single(&values);
	*loaded = true;
}

void	load_sprite(t_image index, char *start, bool *loaded, t_cubed *game)
{
	mlx_texture_t	*tex;
	char			*file;
	char			*end;

	start = ft_skipspaces(start, game);
	end = ft_strrchr(start, '\n');
	file = safe_substr(start, end, game);
	tex = safe_tex(file, true, game);
	free_single(&file);
	game->image[index] = safe_img(0, 0, tex, game);
	*loaded = true;
}

void	load_assets(t_cubed *game)
{
	game->image[IMG_FL] = safe_img(0, 0, safe_tex(TEX_FLOOR, 0, game), game);
	game->image[IMG_RF] = safe_img(0, 0, safe_tex(TEX_ROOF, 0, game), game);
	game->image[IMG_DR] = safe_img(0, 0, safe_tex(TEX_DOOR, 0, game), game);
	game->anim[IMG_W1] = safe_img(0, 0, safe_tex(TEX_WALK1, 0, game), game);
	game->anim[IMG_W2] = safe_img(0, 0, safe_tex(TEX_WALK2, 0, game), game);
	game->anim[IMG_PS] = safe_img(0, 0, safe_tex(TEX_IDLE, 0, game), game);
	game->anim[IMG_MP] = game->anim[IMG_PS];
	game->anim[IMG_T1] = safe_img(0, 0, safe_tex(TEX_TORCH1, 0, game), game);
	game->anim[IMG_T2] = safe_img(0, 0, safe_tex(TEX_TORCH2, 0, game), game);
	game->anim[IMG_T3] = safe_img(0, 0, safe_tex(TEX_TORCH3, 0, game), game);
	game->anim[IMG_T4] = safe_img(0, 0, safe_tex(TEX_TORCH4, 0, game), game);
	game->anim[IMG_T5] = safe_img(0, 0, safe_tex(TEX_TORCH5, 0, game), game);
	game->anim[IMG_T6] = safe_img(0, 0, safe_tex(TEX_TORCH6, 0, game), game);
	game->anim[IMG_TO] = game->anim[IMG_T1];
}
