/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_thread_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:48:41 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/30 11:48:43 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

void	join_threads(t_cubed *game)
{
	int	i;

	i = 0;
	while (i < GAME_THREADS)
	{
		safe_thread(&game->tid[i], THD_JOIN, game);
		i++;
	}
}

void	destroy_mutexes(t_cubed *game)
{
	int	i;

	i = 0;
	while (i < GAME_MUTEXES)
	{
		safe_mutex(&game->mtx[i], MTX_DESTROY, game);
		i++;
	}
}
