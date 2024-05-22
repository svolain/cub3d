/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:33 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/22 15:05:20 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static	void	parse_filename(t_cubed *game)
{
	int	len;

	len = ft_strlen(game->map->file) - 4;
	if (len <= 0 || ft_strcmp(game->map->file + len, ".cub") != 0)
		error_exit(ERR_MAP, MSG_EXTN, game);
	else if (game->map->file[len - 1 == '/'])
		error_exit(ERR_MAP, MSG_FNM, game);
}
/*
void	get_element(t_cubed *game, char *line, char *temp, bool *element)
{
	mlx_texture_t	*tex;

	while(*temp == ' ')
		*temp++;
	temp = ft_skip_whitespace(temp);
	

}

int	check_elements(t_cubed *game, char *line, bool **elements)
{
	char	*temp;
	int		i;

	i = -1;
	temp = ft_skip_whitespace(line);
	if (elements[0] == 0 || ft_strncmp(temp, "NO", 2) == 0)
		get_element(game, line, temp, &elements[0]);
	else if (elements[1] == 0 || ft_strncmp(temp, "SO", 2) == 0)
		get_element(game, line, temp, &elements[1]);
	else if (elements[2] == 0 || ft_strncmp(temp, "WE", 2) == 0)
		get_element(game, line,  temp, &elements[2]);
	else if (elements[3] == 0 || ft_strncmp(temp, "EA", 1) == 0)
		get_element(game, line, temp, &elements[3]);
	else if (elements[4] == 0 || ft_strncmp(temp, "F ", 2) == 0)
		get_color(game, line, temp, &elements[4]);
	else if (elements[6] == 0 || ft_strncmp(temp, "C ", 2) == 0)
		get_color(game, line, temp, &elements[6]);
	else
		error_exit(ERR_MAP, MSG_MPEL, game);
	while (++i < 6)
	{
		if (elements[i] == FALSE)
			return (0);
	}
	return (1);
}*/

static	void	read_elements(t_cubed *game, int *map_start)
{
	char	*line;
	bool	elements[6];
	int		map_flag;

	map_flag = 0;
	while(1)
	{
		*map_start++;
		line = get_next_line(game->map->fd);
		if (line == NULL)
			break ;
		if (!map_flag && *line == '\n' || map_flag == 1 && *line == '\n')
		{
			free(line);
			continue ;
		}
		if (!map_flag)
			map_flag = check_elements(game, line, &elements);
		else
			map_flag++;
		free(line);
	}
	game->map->height = map_flag - 1;
	*map_start -= map_flag;
	close(game->map->fd);
}

void	read_map_info(t_cubed *game, int *map_start)
{
	char	*line;
	char	**grid;
	int		i;
	int		j;

	i = 0;
	j = 0;
	grid = safe_calloc(sizeof(char *) * game->map->height + 1, game);
	ft_bzero(grid, game->map->height + 1);
	while(1)
	{
		if (i++ < *map_start)
			continue ;
		line = get_next_line(game->map->fd);
		if (line == NULL)
			break ;
		grid[j] = line;
		j++;
		free(line);
	}
	if (i < *map_start + 3)
		error_exit(ERR_MAP, MSG_MPEL, game);
}

void	parse_map(t_cubed *game)
{
	int	map_start;

	map_start = 0;
	parse_filename(game);
	game->map->fd = open(game->map->file, O_RDONLY);
	if(game->map->fd == -1)
		error_exit(ERR_MAP, MSG_FILE, game);
	read_elements(game, &map_start);
	if (game->map->height == 0)
		error_exit(ERR_MAP, MSG_VOID, game);
	game->map->fd = open(game->map->file, O_RDONLY);
	if(game->map->fd == -1)
		error_exit(ERR_MAP, MSG_FILE, game);
	read_map_info(game, &map_start);
}
