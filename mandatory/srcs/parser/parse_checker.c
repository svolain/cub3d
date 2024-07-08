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

static int	load_player(t_cubed *game, char c, int y, int x)
{
	static bool	loaded = false;

	if (loaded)
		error_exit(ERR_MAP, MSG_PLAY, game);
	game->cam->x = x * CELLSIZE + CELLSIZE / 2;
	game->cam->y = y * CELLSIZE + CELLSIZE / 2;
	if (c == 'N')
		game->cam->a = NORTH;
	else if (c == 'S')
		game->cam->a = SOUTH;
	else if (c == 'E')
		game->cam->a = EAST;
	else if (c == 'W')
		game->cam->a = WEST;
	if (c == 'N' || c == 'S')
		ft_rotate(&game->cam->a, PI, ROTATE_LEFT);
	rotate_camera(game, ROTATE_RIGHT);
	game->map->matrix[y][x] = MAP_FLOOR;
	loaded = true;
	return (1);
}

void	check_inward(t_cubed *game, char **map)
{
	static int	players = 0;
	int			y;
	int			x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
				map[y][x] = MAP_FLOOR;
			if (!ft_strchr(CHARSET_ALLOWED, map[y][x]))
				error_exit(ERR_MAP, MSG_CHAR, game);
			else if (ft_strchr(CHARSET_PLAYER, map[y][x]))
				players = load_player(game, map[y][x], y, x);
			x++;
		}
		y++;
	}
	if (!players)
		error_exit(ERR_MAP, MSG_PLAY, game);
}

static int	flood_fill(char **map, int y, int x)
{
	int	r;

	r = 0;
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
		return (1);
	else if (map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	r += flood_fill(map, y - 1, x);
	r += flood_fill(map, y + 1, x);
	r += flood_fill(map, y, x - 1);
	r += flood_fill(map, y, x + 1);
	return (r);
}

void	check_walls(t_cubed *game, char **duplex)
{
	int	y;
	int	x;

	y = 0;
	while (duplex[y])
	{
		x = 0;
		while (duplex[y][x])
		{
			if (duplex[y][x] == MAP_FLOOR
				&& flood_fill(duplex, y, x))
				error_exit(ERR_MAP, MSG_WALL, game);
			x++;
		}
		y++;
	}
}
