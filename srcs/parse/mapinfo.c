/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:50:03 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/29 15:38:22 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	update_player_data(t_cubed *game, char c, int i, int j)
{
	static bool loaded = false;

	if (loaded)
		error_exit(ERR_MAP, MSG_PLAY, game);
	game->cam->x = j * CELLSIZE;
	game->cam->y = i * CELLSIZE;
	if (c == 'N')
		game->cam->a = NORTH - 0.001;
	else if (c == 'S')
		game->cam->a = SOUTH - 0.001;
	else if (c == 'E')
		game->cam->a = EAST - 0.001;
	else if (c == 'W')
		game->cam->a = WEST - 0.001;
	game->map->matrix[i][j] = '0';
	loaded = true;
}

void	check_map_characters(t_cubed *game, char **map)
{
	int		i;
	int		j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '0';
			if (!ft_strchr(MAP_CHARSET, map[i][j]))
				error_exit(ERR_MAP, MSG_CHAR, game);
			else if (ft_strchr(PLAYER_SET, map[i][j]))
				update_player_data(game, map[i][j], i, j);
			j++;
		}
		i++;
	}
}

int	check_wall(char **map, int i, int j)
{
	int	r;

	r = 0;
	if (i < 0 || j < 0 || (map[i] && !map[i][j]))
		return (1);
	else if (map[i][j] == '1')
		return (0);
	map[i][j] = '1';
	r += check_wall(map, i - 1, j);
	r += check_wall(map, i + 1, j);
	r += check_wall(map, i, j - 1);
	r += check_wall(map, i, j + 1);
	return (r);
}

void	validate_walls(t_cubed *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == '0' && check_wall(map, i, j))
			{
				free_double(&map);
				error_exit(ERR_MAP, MSG_WALL, game);
			}
			j++;
		}
		i++;
	}
}

char	*prefilter(t_cubed *game)
{
	while (true)
	{
		free_single(&game->gnl);
		game->gnl = get_next_line(game->map->filefd);
		if (!game->gnl)
			error_exit(ERR_MAP, MSG_NOMP, game);
		if (ft_isemptyline(game->gnl))
			continue ;
		else if (*game->gnl != '1' && *game->gnl != ' ')
			error_exit(ERR_MAP, MSG_WALL, game);
		break ;
	}
	return (game->gnl);
}

void	parse_mapinfo(t_cubed *game)
{
	char	*buffer;
	char	*joined;
	char	**duplex;

	buffer = prefilter(game);
	while(true)
	{
		game->map->height++;
		game->gnl = get_next_line(game->map->filefd);
		if (!game->gnl)
			break ;
		if ((int)ft_strlen(game->gnl) > game->map->width)
			game->map->width = ft_strlen(game->gnl);
		joined = safe_strjoin(buffer, game->gnl, game);
		free_single(&buffer);
		free_single(&game->gnl);
		buffer = joined;
	}
	game->map->matrix = safe_split(joined, '\n', game);
	duplex = safe_split(joined, '\n', game);
	free(joined);
	validate_walls(game, duplex);
	free_double(&duplex);
	check_map_characters(game, game->map->matrix);
}
