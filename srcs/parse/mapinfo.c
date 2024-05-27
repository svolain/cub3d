/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:50:03 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/27 18:59:30 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	update_player_data(t_cubed *game, char c, int i, int j)
{
	static bool loaded = false;

	if (loaded)
		error_exit(ERR_MAP, MSG_PLAY, game);
	game->cam->x = j;
	game->cam->y = i;
	if (c == 'N')
		game->cam->a = NORTH;
	else if (c == 'S')
		game->cam->a = SOUTH;
	else if (c == 'E')
		game->cam->a = EAST;
	else if (c == 'W')
		game->cam->a = WEST;
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
	char	*temp;

	while (true)
	{
		free_single(&game->gnl);
		game->gnl = get_next_line(game->map->filefd);
		if (!game->gnl)
			error_exit(ERR_MAP, MSG_NOMP, game);
		temp = game->gnl;
		while(*temp && ft_isspace(*temp))
			temp++;
		if (!*temp)
			continue ;
		else if (*temp != '1')
			error_exit(ERR_MAP, MSG_WALL, game);
		break ;
	}
	return (game->gnl);
}

void	parse_mapinfo(t_cubed *game)
{
	char	*buffer;
	char	*join;
	char	**map_dup;

	buffer = prefilter(game);
	while(true)
	{
		game->gnl = get_next_line(game->map->filefd);
		if (!game->gnl)
			break ;
		join = safe_strjoin(buffer, game->gnl, game);
		free(buffer);
		buffer = join;
		free(game->gnl);
	}
	game->map->matrix = safe_split(join, '\n', game);
	free(join);
	game->map->height = ft_arrlen(game->map->matrix);
	map_dup = dup_arr(game->map->matrix, game->map->height, game);
	validate_walls(game, map_dup);
	free_double(&map_dup);
	check_map_characters(game, game->map->matrix);
}
