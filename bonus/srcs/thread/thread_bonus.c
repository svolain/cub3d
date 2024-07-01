/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 05:43:41 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/28 13:56:59 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

static char	*err_msg(int exitcode, t_operation action)
{
	if (exitcode == ESRCH && (action == THD_DETACH || action == THD_JOIN))
		return ("No thread with ID could be found.\n");
	else if (exitcode == EINVAL && (action == THD_DETACH || action == THD_JOIN))
		return ("Thread is not a joinable thread.\n");
	else if (exitcode == EDEADLK && action == THD_JOIN)
		return ("Deadlock was detected.\n");
	else if (exitcode == EAGAIN && action == THD_CREATE)
		return ("Insufficient resources to create another thread.\n");
	else
		return ("Unhandled <safe_thread> error occured.\n");
}

static char	*fn_name(t_operation action)
{
	if (action == THD_CREATE)
		return ("<pthread_create>: ");
	else if (action == THD_DETACH)
		return ("<pthread_detach>: ");
	else
		return ("<pthread_join>: ");
}

static void	err_chkr(int exitcode, t_operation action, t_cubed *game)
{
	if (exitcode != SUCCESS)
	{
		error_log(MSG_SYSC, fn_name(action), err_msg(exitcode, action));
		error_fatal(EXIT_FAILURE, NULL, game);
	}
}

static void	create_threads(t_operation action, t_cubed *game)
{
	err_chkr(pthread_create(&game->tid[THD_FG],
			NULL, render_walls, game), action, game);
	err_chkr(pthread_create(&game->tid[THD_BG],
			NULL, render_floor, game), action, game);
	err_chkr(pthread_create(&game->tid[THD_OL],
			NULL, render_sprites, game), action, game);
	err_chkr(pthread_create(&game->tid[THD_MM],
			NULL, render_minimap, game), action, game);
	err_chkr(pthread_create(&game->tid[THD_FV],
			NULL, render_fov, game), action, game);
}

void	safe_thread(pthread_t *tid, t_operation action, t_cubed *game)
{
	if (action == THD_CREATE)
		create_threads(action, game);
	else if (action == THD_JOIN)
		err_chkr(pthread_join(*tid, NULL), action, game);
	else if (action == THD_DETACH)
		err_chkr(pthread_detach(*tid), action, game);
}
