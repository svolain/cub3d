/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:50:03 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/31 10:58:06 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static void	error_occured(char *str, char *errmsg, t_cubed *game)
{
	if (str != NULL)
		free_single(&str);
	error_exit(ERR_MAP, errmsg, game);
}

static void	parse_map(char *joined, t_cubed *game)
{
	if (game->map->height < 3 || game->map->width < 3)
		error_occured(joined, MSG_SMALL, game);
	else if (game->map->height > MAPLIMIT
		|| game->map->width > MAPLIMIT)
		error_occured(joined, MSG_LARGE, game);
	else if (ft_has_extra_delimiter(joined, '\n'))
		error_occured(joined, MSG_BLANK, game);
	game->map->matrix = safe_split(joined, '\n', game);
	game->map->duplex = safe_split(joined, '\n', game);
	free_single(&joined);
	check_walls(game, game->map->duplex);
	check_inward(game, game->map->matrix);
}

static char	*prefilter(t_cubed *game)
{
	while (true)
	{
		free_single(&game->gnl);
		game->gnl = get_next_line(game->map->filefd);
		if (!game->gnl)
			error_exit(ERR_MAP, MSG_NOMAP, game);
		if (ft_is_empty_line(game->gnl))
			continue ;
		else if (*game->gnl != MAP_WALL && *game->gnl != ' ')
			error_exit(ERR_ELEM, MSG_ELEM, game);
		break ;
	}
	return (game->gnl);
}

void	parse_mapinfo(t_cubed *game)
{
	char	*buffer;
	char	*joined;

	joined = NULL;
	buffer = prefilter(game);
	while (true)
	{
		game->map->height++;
		game->gnl = get_next_line(game->map->filefd);
		if (!game->gnl)
			break ;
		if ((int)ft_strlen(game->gnl) > game->map->width)
			game->map->width = ft_strlen(game->gnl);
		joined = safe_strjoin(buffer, game->gnl, game);
		free_single(&game->gnl);
		free_single(&buffer);
		buffer = joined;
	}
	parse_map(joined, game);
}
