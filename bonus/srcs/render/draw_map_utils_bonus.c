/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 23:39:25 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/26 11:31:26 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

int	ft_is_grid(int x, int y)
{
	return (x % MAPCELL == 0 || y % MAPCELL == 0);
}

int	ft_is_border(int x, int y)
{
	return (y < MAPBORDER || y > MAPSIZE - MAPBORDER
		|| x < MAPBORDER || x > MAPSIZE - MAPBORDER);
}

bool	ft_inside_map(int x, int y, t_cubed *game)
{
	int		map[2];

	get_map_position(map, x, y);
	if (map[X] < 0 || map[X] >= game->map->width
		|| map[Y] < 0 || map[Y] >= game->map->height)
		return (false);
	return (true);
}

char	ft_in_elements(int x, int y, char *set, t_cubed *game)
{
	int		map[2];
	char	c;

	get_map_position(map, x, y);
	c = get_map_element(map[X], map[Y], game);
	if (ft_strchr(set, c))
		return (c);
	return (0);
}

char	ft_in_sprite(int map[2], t_camera *cam, t_cubed *game)
{
	int		player[2];
	char	c;

	get_map_position(player, cam->x, cam->y);
	if (player[X] == map[X] && player[Y] == map[Y])
	{
		c = get_map_element(player[X], player[Y], game);
		if (c == MAP_EXIT)
		{
			printf("You won the game\n");
			set_game_over(game);
			return (MAP_EXIT);
		}
		set_map_element(map[X], map[Y], MAP_FLOOR, game);
		return (c);
	}
	return (0);
}
