/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:32:28 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/28 12:35:32 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_BONUS_H
# define MULTI_BONUS_H

# include <pthread.h>

# define GAME_THREADS 6
# define GAME_MUTEXES 8
# define GAME_STATS 2

typedef pthread_mutex_t	t_mtx;

typedef enum e_thread
{
	THD_BG,
	THD_FG,
	THD_OL,
	THD_MM,
	THD_FV,
	THD_HD
}	t_thread;

typedef enum e_mutex
{
	MTX_DONE,
	MTX_LOADED,
	MTX_CAM,
	MTX_PLR,
	MTX_MAP,
	MTX_WPN,
	MTX_GATE,
	MTX_FX
}	t_mutex;

typedef enum e_status
{
	STAT_DONE,
	STAT_LOADED
}	t_status;

typedef enum e_operation
{
	THD_CREATE,
	THD_JOIN,
	THD_DETACH,
	MTX_INIT,
	MTX_LOCK,
	MTX_UNLOCK,
	MTX_DESTROY
}	t_operation;

#endif
