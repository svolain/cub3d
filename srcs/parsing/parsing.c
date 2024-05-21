/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:45:33 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/21 17:32:11 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static	void	parse_filename(t_cubed *game)
{
	int	len;

	len = ft_strlen(game->map->file) - 4;
	if (len < 5 || ft_strcmp(game->map->file + len, ".ber") != 0)
		error_exit(ERR_MAP, MSG_EXTN, game);
	else if (game->map->file[len - 1 == '/'])
		error_exit(ERR_MAP, MSG_FNM, game);
}

void	red_file(t_cubed *game)
{
	char *line;
	int		conf_last_line;

	int		conf_last_line = 0;
	while(1)
	{
		line = get_next_line(game->map->fd);
		if (line == NULL)
			break ;
		if (*line == '\n')
		{
			free(line);
			continue ;
		}
		// check wheter we have reached to map or still readin non map elements
		if ()
			
		else
	}
}

void	parse_file_content(t_cubed *game)
{
	game->map->fd = open(game->map->file, O_RDONLY);
	if(game->map->fd == -1)
		error_exit(ERR_MAP, MSG_FILE, game);
	read_file(game);

}

void	parse_map(t_cubed *game)
{
		parse_filename(game);
		parse_file_content(game);
}