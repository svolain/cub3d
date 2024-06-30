/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getset_plr_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:56:59 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/30 14:57:02 by jmertane         ###   ########.fr       */
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

int	get_player_value(char *str, t_cubed *game)
{
	int	value;

	safe_mutex(&game->mtx[MTX_PLR], MTX_LOCK, game);
	value = ft_atoi(str);
	safe_mutex(&game->mtx[MTX_PLR], MTX_UNLOCK, game);
	return (value);
}

char	*get_player_str(char **str, t_cubed *game)
{
	char	*value;

	safe_mutex(&game->mtx[MTX_PLR], MTX_LOCK, game);
	value = *str;
	safe_mutex(&game->mtx[MTX_PLR], MTX_UNLOCK, game);
	return (value);
}
