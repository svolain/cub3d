/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:48:31 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/27 19:15:16 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static int	load_element(bool *elements, char *id, t_cubed *game)
{
	if (!elements[IMG_NO] && !ft_strncmp(id, "NO ", 3))
		load_sprite(IMG_NO, id + 2, &elements[IMG_NO], game);
	else if (!elements[IMG_SO] && !ft_strncmp(id, "SO ", 3))
		load_sprite(IMG_SO, id + 2, &elements[IMG_SO], game);
	else if (!elements[IMG_WE] && !ft_strncmp(id, "WE ", 3))
		load_sprite(IMG_WE, id + 2, &elements[IMG_WE], game);
	else if (!elements[IMG_EA] && !ft_strncmp(id, "EA ", 3))
		load_sprite(IMG_EA, id + 2, &elements[IMG_EA], game);
	else if (!elements[IMG_F] && !ft_strncmp(id, "F ", 2))
		load_color(COL_F, id + 1, &elements[IMG_F], game);
	else if (!elements[IMG_C] && !ft_strncmp(id, "C ", 2))
		load_color(COL_C, id + 1, &elements[IMG_C], game);
	else
		error_exit(ERR_ELEM, MSG_ELEM, game);
	return (1);
}

void	parse_elements(t_cubed *game)
{
	static int	loaded = 0;
	static bool	elements[6];

	while (true)
	{
		free_single(&game->gnl);
		if (loaded == 6)
			break ;
		game->gnl = get_next_line(game->map->filefd);
		if (!game->gnl)
			break ;
		if (ft_isemptyline(game->gnl))
			continue ;
		loaded += load_element(elements, game->gnl, game);
	}
}
