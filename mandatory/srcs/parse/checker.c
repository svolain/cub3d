/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:59:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/31 19:59:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static int	load_player(t_cubed *game, char c, int i, int j)
{
	static bool	loaded = false;

	if (loaded)
		error_exit(ERR_MAP, MSG_PLAY, game);
	game->cam->x = j * CELLSIZE;
	game->cam->y = i * CELLSIZE;
	if (c == 'N')
		game->cam->a = NORTH;
	else if (c == 'S')
		game->cam->a = SOUTH;
	else if (c == 'E')
		game->cam->a = EAST;
	else if (c == 'W')
		game->cam->a = WEST;
	game->map->matrix[i][j] = MAP_FLOOR;
	if (c == 'N' || c == 'S')
		ft_rotate(&game->cam->a, PI, ROTATE_LEFT);
	ft_rotate(&game->cam->a, STEP_ANGLE, ROTATE_RIGHT);
	loaded = true;
	return (1);
}

void	check_inward(t_cubed *game, char **map)
{
	int		players;
	int		i;
	int		j;

	i = 0;
	players = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = MAP_FLOOR;
			if (!ft_strchr(CHARSET_ALLOWED, map[i][j]))
				error_exit(ERR_MAP, MSG_CHAR, game);
			else if (ft_strchr(CHARSET_PLAYER, map[i][j]))
				players = load_player(game, map[i][j], i, j);
			j++;
		}
		i++;
	}
	if (!players)
		error_exit(ERR_MAP, MSG_PLAY, game);
}

static int	flood_fill(char **map, int i, int j)
{
	int	r;

	r = 0;
	if (i < 0 || j < 0 || (map[i] && !map[i][j]))
		return (1);
	else if (map[i][j] == '1')
		return (0);
	map[i][j] = '1';
	r += flood_fill(map, i - 1, j);
	r += flood_fill(map, i + 1, j);
	r += flood_fill(map, i, j - 1);
	r += flood_fill(map, i, j + 1);
	return (r);
}

void	check_walls(t_cubed *game, char **duplex)
{
	int	i;
	int	j;

	i = 0;
	while (duplex[i])
	{
		j = 0;
		while (duplex[i][j])
		{
			if (duplex[i][j] == '0' && flood_fill(duplex, i, j))
			{
				free_double(&duplex);
				error_exit(ERR_MAP, MSG_WALL, game);
			}
			j++;
		}
		i++;
	}
}
