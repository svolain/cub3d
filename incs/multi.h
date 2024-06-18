/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:32:28 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 14:15:08 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTI_H
# define MULTI_H

# define GAME_THREADS 4
# define GAME_MUTEXES 3
# define GAME_STATS 1

typedef pthread_mutex_t	t_mtx;

typedef enum e_thread
{
	THD_BG,
	THD_FG,
	THD_MM,
	THD_MR
}	t_thread;

typedef enum e_mutex
{
	MTX_DONE,
	MTX_CAM,
	MTX_MAP,
}	t_mutex;

typedef enum e_status
{
	STAT_DONE
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
