/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:48:31 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/26 22:48:14 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static int	load_element(bool *elements, char *id, t_cubed *game)
{
	if (!elements[ELEM_NO] && !ft_strncmp(id, "NO ", 3))
		load_sprite(ELEM_NO, id + 2, &elements[ELEM_NO], game);
	else if (!elements[ELEM_SO] && !ft_strncmp(id, "SO ", 3))
		load_sprite(ELEM_SO, id + 2, &elements[ELEM_SO], game);
	else if (!elements[ELEM_WE] && !ft_strncmp(id, "WE ", 3))
		load_sprite(ELEM_WE, id + 2, &elements[ELEM_WE], game);
	else if (!elements[ELEM_EA] && !ft_strncmp(id, "EA ", 3))
		load_sprite(ELEM_EA, id + 2, &elements[ELEM_EA], game);
	else if (!elements[ELEM_F] && !ft_strncmp(id, "F ", 2))
		load_color(COL_F, id + 1, &elements[ELEM_F], game);
	else if (!elements[ELEM_C] && !ft_strncmp(id, "C ", 2))
		load_color(COL_C, id + 1, &elements[ELEM_C], game);
	else
		error_exit(ERR_ELEM, MSG_ELEM, game);
	return (1);
}

static int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static bool	ft_isempty(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (!*str)
		return (true);
	return (false);
}

void	parse_elements(t_cubed *game)
{
	static int	loaded = 0;
	static bool	elements[6];

	while (true)
	{
		free_single(&game->gnl);
		if (loaded == 6)
			break ;
		game->gnl = get_next_line(game->map->filefd);
		if (!game->gnl)
			break ;
		if (ft_isempty(game->gnl))
			continue ;
		loaded += load_element(elements, game->gnl, game);
	}
}
