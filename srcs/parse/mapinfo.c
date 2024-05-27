/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:50:03 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/27 16:49:54 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

/*
static	void	check_if_closed(t_cubed *g, int *i, int *j, int *start_end)
{
	int	next_len;
	int	prev_len;

	prev_len = start_end[0];
	next_len = ft_strlen(g->map->matrix[*i + 1]);
	if (j > prev_len)
		return ;
	if (g->map->matrix[*i - 1][*j] != '1' && g->map->matrix[*i - 1][*j] != ' ')
		error_exit(ERR_MAP, MSG_WALL, g);
	if ( j > next_len)
		return ;
	if (g->map->matrix[*i + 1][*j] != '1' && g->map->matrix[*i + 1][*j] != ' ')
		error_exit(ERR_MAP, MSG_WALL, g);
	if (g->map->matrix[*i][*j - 1] != '1' && g->map->matrix[*i][*j - 1] != ' ')
		error_exit(ERR_MAP, MSG_WALL, g);
	if (g->map->matrix[*i][*j + 1] != '1' &&
		g->map->matrix[*i][*j + 1] != ' ' && g->map->matrix[*i][*j + 1] != '\0')
		error_exit(ERR_MAP, MSG_WALL, g);
}

static	void	validate_edge_line(t_cubed *g, int *i, int *j, int *start_end)
{
	while(g->map->matrix[*i][*j])
	{
		if (g->map->matrix[*i + 1] == 0)
		{
			if (start_end[0] > start_end[1] - 2)
				error_exit(ERR_MAP, MSG_WALL, g);
			if (g->map->matrix[*i][*j] != '1' && g->map->matrix[*i][*j] != ' ')
				error_exit(ERR_MAP, MSG_WALL, g);
			if (g->map->matrix[*i][*j] == ' ' && j <= start_end[1])
				if (g->map->matrix[*i - 1][*j] != '1' &&
					g->map->matrix[*i - 1][*j] != ' ')
					error_exit(ERR_MAP, MSG_WALL, g);
		}
		else if (*i == 0)
		{
			if (g->map->matrix[*i][*j] != '1' && g->map->matrix[*i][*j] != ' ')
				error_exit(ERR_MAP, MSG_WALL, g);
			if (g->map->matrix[*i][*j] == ' ' && )
				if (g->map->matrix[*i + 1][*j] != '1' &&
					g->map->matrix[*i + 1][*j] != ' ')
		}
		*j++;
	}
}

static	void	validate_middle_line(t_cubed *g, int *i, int *j, int *start_end)
{
	if (start_end[0] > start_end[1] - 2)
		error_exit(ERR_MAP, MSG_WALL, g);
	if (g->map->matrix[*i][*j] != '1')
		error_exit(ERR_MAP, MSG_WALL, g);
	*j++;
	while(g->map->matrix[*i][*j])
	{
		if (j >= start_end[1] && g->map->matrix[*i][*j] != '1')
			error_exit(ERR_MAP, MSG_WALL, g);
		if (g->map->matrix[*i][*j] != '0' && g->map->matrix[*i][*j] != '2' &&
			g->map->matrix[*i][*j] != '1' && g->map->matrix[*i][*j] != ' ')
			error_exit(ERR_MAP, MSG_WALL, g);
		if (g->map->matrix[*i][*j] == ' ')
			check_if_closed(g, &i, &j, start_end);
		*j++;
	}

}
static	void	validate_map(t_cubed *game)
{
	int	start_end[2];
	int	i;
	int	j;

	i = -1;
	while(game->map->matrix[++i])
	{
		j = -1;
		start_end[0] = 0;
		while(game->map->matrix[i][j])
		{
			if (ft_isspace(game->map->matrix[i][++j]))
			{
				if (i > 0 && game->map->matrix[i - 1][j] != '1' &&
					game->map->matrix[i - 1][j] != ' ')
						error_exit(ERR_MAP, MSG_WALL, game);
				start_end[0] = j + 1;
			}
		}
		if (i == 0 || game->map->matrix[i + 1] == 0)
			validate_edge_line(game, &i, &j, start_end);
		else
			validate_middle_line(game, &i, &j, start_end);
		start_end[1] = j;
	}
}
*/

void	validate_walls(t_cubed *game, int x, int y)
{
	int		len;
	char	**temp;

	temp = game->map->matrix;
	len = ft_strlen(temp[x]);
	int i = 0;
	if (temp[x][y] == ' ')
		validate_walls(game, x, y + 1);
	if (temp[x][y] == '1')
		temp[x][y] = 'o';
	while(temp[i])
		printf("%s\n", temp[i++]);
	printf("\n\n");
	printf("y: %d x: %d mh: %d\n", y, x, game->map->height);
	
	if (y < len - 1 && temp[x][y + 1] == '1')
		validate_walls(game, x, y + 1);
	else if (x < game->map->height - 1 && temp[x + 1][y] == '1')
		validate_walls(game, x + 1, y);
	else if (y > 0 && temp[x][y - 1] == '1')
		validate_walls(game, x, y - 1);
	else if (x > 0 && temp[x - 1][y] == '1')
		validate_walls(game, x - 1, y);
	return ;
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
		while (*temp && ft_isspace(*temp))
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

	buffer = prefilter(game);
	while (true)
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
	validate_walls(game, 0, 0);
}
