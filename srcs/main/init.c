/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/26 18:49:48 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	open_infile(t_cubed *game)
{
	t_mapinfo	*map;
	char		*file;
	char		buffer;

	map = game->map;
	file = map->filename;
	map->filefd = open(file, O_DIRECTORY);
	if (map->filefd != FAILURE)
		error_exit(ERR_MAP, MSG_FLDR, game);
	map->filefd = open(file, O_RDONLY);
	if (map->filefd == FAILURE)
		error_exit(ERR_MAP, strerror(errno), game);
	read(map->filefd, &buffer, sizeof(char));
	if (!buffer)
		error_exit(ERR_MAP, MSG_VOID, game);
	close(map->filefd);
	map->filefd = open(file, O_RDONLY);
}

static void	parse_filename(t_cubed *game)
{
	char	*file;
	char	*extn;
	int		len;

	file = game->map->filename;
	extn = ft_strrchr(file, '.');
	len = ft_strlen(file) - 4;
	if (len <= 0 || !extn || ft_strncmp(extn, ".cub", 5))
		error_exit(ERR_MAP, MSG_EXTN, game);
	if (len > 0 && !ft_strncmp(extn - 1, "/.cub", 6))
		error_exit(ERR_MAP, MSG_NAME, game);
}

void	init_game(t_cubed *game, char *file)
{
	ft_bzero(game, sizeof(t_cubed));
	game->cam = safe_calloc(sizeof(t_vector), game);
	game->map = safe_calloc(sizeof(t_mapinfo), game);
	game->map->filename = file;
	game->map->filefd = -1;
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE, false);
	if (!game->mlx)
		error_exit(ERR_MLX, MSG_MLX, game);
	parse_filename(game);
	open_infile(game);
	parse_elements(game);
	parse_mapinfo(game);
	//int i = 0;
	/*while(game->map->matrix[i])
		printf("%s", game->map->matrix[i]);*/
	/*  init_minimap(game); */
}
