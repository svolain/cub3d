/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:48:31 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/31 14:44:46 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static int	load_element(bool *elements, char *id, t_cubed *game)
{
	if (!elements[0] && !ft_strncmp(id, "NO ", 3))
		load_sprite(IMG_NO, id + 2, &elements[0], game);
	else if (!elements[1] && !ft_strncmp(id, "SO ", 3))
		load_sprite(IMG_SO, id + 2, &elements[1], game);
	else if (!elements[2] && !ft_strncmp(id, "WE ", 3))
		load_sprite(IMG_WE, id + 2, &elements[2], game);
	else if (!elements[3] && !ft_strncmp(id, "EA ", 3))
		load_sprite(IMG_EA, id + 2, &elements[3], game);
	else if (!elements[4] && !ft_strncmp(id, "F ", 2))
		load_color(COL_F, id + 1, &elements[4], game);
	else if (!elements[5] && !ft_strncmp(id, "C ", 2))
		load_color(COL_C, id + 1, &elements[5], game);
	else
		error_exit(ERR_ELEM, MSG_ELEM, game);
	return (1);
}

void	parse_elements(t_cubed *game)
{
	static bool	elements[6];
	static int	loaded = 0;

	while (true)
	{
		free_single(&game->gnl);
		if (loaded == 6)
			break ;
		game->gnl = get_next_line(game->map->filefd);
		if (!game->gnl)
			error_exit(ERR_ELEM, MSG_ELEM, game);
		if (ft_isemptyline(game->gnl))
			continue ;
		loaded += load_element(elements, game->gnl, game);
	}
}
