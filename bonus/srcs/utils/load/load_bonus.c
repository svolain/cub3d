/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:04:40 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/07 12:15:52 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

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
	game->color[index] = get_rgba(rgba[0], rgba[1], rgba[2], 125);
	free_double(&colors);
	free_single(&values);
	*loaded = true;
}

void	load_texture(t_image index, char *start, bool *loaded, t_cubed *game)
{
	mlx_texture_t	*tex;
	char			*file;
	char			*end;

	start = ft_skipspaces(start, game);
	end = ft_strrchr(start, '\n');
	file = safe_substr(start, end, game);
	tex = safe_tex(file, true, game);
	free_single(&file);
	game->asset[index] = safe_img(0, 0, tex, game);
	*loaded = true;
}

void	init_sprite(int index, int frame_count, double delay, t_cubed *game)
{
	game->sprite[index] = safe_calloc(sizeof(t_sprite), game);
	game->sprite[index]->delay = delay;
	game->sprite[index]->frame_count = frame_count;
	game->sprite[index]->current_frame = IMG_BASE;
	game->sprite[index]->frame = safe_calloc
		(frame_count * sizeof(mlx_image_t*), game);
}
