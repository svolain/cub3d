/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:11:43 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 14:01:55 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	set_player_value(char **str, int value, t_cubed *game)
{
	safe_mutex(&game->mtx[MTX_PLR], MTX_LOCK, game);
	if (*str != NULL)
		free_single(str);
	*str = safe_itoa(value, game);
	safe_mutex(&game->mtx[MTX_PLR], MTX_UNLOCK, game);
}

char	*draw_player_value(char *str, t_cubed *game)
{
	char	*value;

	safe_mutex(&game->mtx[MTX_PLR], MTX_LOCK, game);
	value = str;
	safe_mutex(&game->mtx[MTX_PLR], MTX_UNLOCK, game);
	return (value);
}

int	get_player_value(char *str, t_cubed *game)
{
	int	value;

	safe_mutex(&game->mtx[MTX_PLR], MTX_LOCK, game);
	value = ft_atoi(str);
	safe_mutex(&game->mtx[MTX_PLR], MTX_UNLOCK, game);
	return (value);
}

void	set_camera(t_camera *cam, t_cubed *game)
{
	safe_mutex(&game->mtx[MTX_CAM], MTX_LOCK, game);
	game->cam->a = cam->a;
	game->cam->x = cam->x;
	game->cam->y = cam->y;
	game->cam->dx = cam->dx;
	game->cam->dy = cam->dy;
	safe_mutex(&game->mtx[MTX_CAM], MTX_UNLOCK, game);
}

void	get_camera(t_camera *cam, t_cubed *game)
{
	safe_mutex(&game->mtx[MTX_CAM], MTX_LOCK, game);
	cam->a = game->cam->a;
	cam->x = game->cam->x;
	cam->y = game->cam->y;
	cam->dx = game->cam->dx;
	cam->dy = game->cam->dy;
	safe_mutex(&game->mtx[MTX_CAM], MTX_UNLOCK, game);
}
