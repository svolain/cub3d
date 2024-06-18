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

#include <cubed.h>

static void	parse_map(char *joined, t_cubed *game)
{
	char	**duplex;

	game->map->matrix = safe_split(joined, '\n', game);
	duplex = safe_split(joined, '\n', game);
	free_single(&joined);
	check_walls(game, duplex);
	free_double(&duplex);
	check_inward(game, game->map->matrix);
	if (game->map->height > MAXSIZE || game->map->width > MAXSIZE)
		error_exit(ERR_MAP, MSG_SIZE, game);
}

static char	*prefilter(t_cubed *game)
{
	while (true)
	{
		free_single(&game->gnl);
		game->gnl = get_next_line(game->map->filefd);
		if (!game->gnl)
			error_exit(ERR_MAP, MSG_NOMP, game);
		if (ft_isemptyline(game->gnl))
			continue ;
		else if (*game->gnl != MAP_WALL && *game->gnl != ' ')
			error_exit(ERR_MAP, MSG_WALL, game);
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
