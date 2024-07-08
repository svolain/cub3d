/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:01:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/24 08:23:05 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static void	error_occured(int fd, char *file, char *errmsg, t_cubed *game)
{
	if (fd != FAILURE)
		close(fd);
	if (file != NULL)
		free_single(&file);
	error_exit(ERR_ELEM, errmsg, game);
}

void	parse_texture(t_cubed *game, char *file)
{
	char	buffer;
	int		fd;

	fd = FAILURE;
	fd = open(file, O_DIRECTORY);
	if (fd != FAILURE)
		error_occured(fd, file, MSG_FLDR, game);
	fd = open(file, O_RDONLY);
	if (fd == FAILURE)
		error_occured(fd, file, strerror(errno), game);
	if (!ft_has_extension(file, ".png"))
		error_occured(fd, file, MSG_EXTN, game);
	if (!ft_has_filename(file, "/.png"))
		error_occured(fd, file, MSG_NAME, game);
	(void)read(fd, &buffer, sizeof(char));
	if (!buffer)
		error_occured(fd, file, MSG_EMPTY, game);
	close(fd);
}

void	parse_filename(t_cubed *game, char *file)
{
	char	buffer;

	game->map->filefd = open(file, O_DIRECTORY);
	if (game->map->filefd != FAILURE)
		error_exit(ERR_MAP, MSG_FLDR, game);
	game->map->filefd = open(file, O_RDONLY);
	if (game->map->filefd == FAILURE)
		error_exit(ERR_MAP, strerror(errno), game);
	if (!ft_has_extension(file, ".cub"))
		error_exit(ERR_MAP, MSG_EXTN, game);
	if (!ft_has_filename(file, "/.cub"))
		error_exit(ERR_MAP, MSG_NAME, game);
	(void)read(game->map->filefd, &buffer, sizeof(char));
	if (!buffer)
		error_exit(ERR_MAP, MSG_EMPTY, game);
	close(game->map->filefd);
	game->map->filefd = open(file, O_RDONLY);
}
