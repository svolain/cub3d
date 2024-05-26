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

static	void	error_occured(char *str, char **arr, t_cubed *game)
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
	if (iteration > 2)
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

static char	*skip_spaces(char *start, t_cubed *game)
{
	while (*start && *start == ' ')
		start++;
	if (!*start || *start == '\n')
		error_exit(ERR_ELEM, MSG_ELEM, game);
	return (start);
}

void	load_color(t_element index, char *start, bool *loaded, t_cubed *game)
{
	int32_t	rgba[4];
	char	**arr;
	char	*values;
	char	*end;
	int		i;

	start = skip_spaces(start, game);
	end = ft_strchr(start, '\n');
	values = safe_substr(start, end, game);
	arr = safe_split(values, ',', game);
	i = 0;
	while (arr[i])
	{
		rgba[i] = parse_color(arr[i], i);
		if (rgba[i] == FAILURE)
			error_occured(values, arr, game);
		i++;
	}
	game->col[index] = get_rgba(rgba[0], rgba[1], rgba[2], 255);
	*loaded = true;
}

void	load_sprite(t_element index, char *start, bool *loaded, t_cubed *game)
{
	mlx_texture_t	*tex;
	char			*file;
	char			*end;

	start = skip_spaces(start, game);
	end = ft_strchr(start, '\n');
	file = safe_substr(start, end, game);
	tex = safe_texture(file, game);
	game->img[index] = safe_image(0, 0, tex, game);
	mlx_delete_texture(tex);
	free_single(&file);
	*loaded = true;
}
