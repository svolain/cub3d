/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:12:26 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 09:39:15 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static char	*err_msg(int exitcode, t_operation action)
{
	if (exitcode == EINVAL && (action == MTX_LOCK || action == MTX_UNLOCK))
		return ("Mutex has not been properly initialized.\n");
	else if (exitcode == EDEADLK && action == MTX_LOCK)
		return ("Mutex is already locked by calling thread.\n");
	else if (exitcode == EPERM && action == MTX_UNLOCK)
		return ("Calling thread does not own the mutex.\n");
	else if (exitcode == EBUSY && action == MTX_DESTROY)
		return ("Mutex is currently locked.\n");
	else
		return ("Unhandled <safe_mutex> error occured.\n");
}

static char	*fn_name(t_operation action)
{
	if (action == MTX_LOCK)
		return ("<pthread_mutex_lock>: ");
	else if (action == MTX_UNLOCK)
		return ("<pthread_mutex_unlock>: ");
	else if (action == MTX_INIT)
		return ("<pthread_mutex_init>: ");
	else
		return ("<pthread_mutex_destroy>: ");
}

static void	err_chkr(int exitcode, t_operation action, t_cubed *game)
{
	if (exitcode != SUCCESS)
	{
		error_log(MSG_SYSC, fn_name(action), err_msg(exitcode, action));
		error_fatal(EXIT_FAILURE, NULL, game);
	}
}

static void	init_mutexes(t_operation action, t_cubed *game)
{
	t_mtx	mutex;
	int		i;

	i = 0;
	while (i < GAME_MUTEXES)
	{
		mutex = game->mtx[i];
		err_chkr(pthread_mutex_init(&mutex, NULL), action, game);
		i++;
	}
}

void	safe_mutex(t_mtx *mutex, t_operation action, t_cubed *game)
{
	if (action == MTX_INIT)
		init_mutexes(action, game);
	else if (action == MTX_LOCK)
		err_chkr(pthread_mutex_lock(mutex), action, game);
	else if (action == MTX_UNLOCK)
		err_chkr(pthread_mutex_unlock(mutex), action, game);
	else if (action == MTX_DESTROY)
		err_chkr(pthread_mutex_destroy(mutex), action, game);
}
