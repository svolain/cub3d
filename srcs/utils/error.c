/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:57:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/27 15:01:18 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

static void	error_log(char *msg1, char *msg2, char *msg3)
{
	ft_putstr_fd(FMT_BOLD_RED, STDERR_FILENO);
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd(msg1, STDERR_FILENO);
	ft_putstr_fd(msg2, STDERR_FILENO);
	ft_putstr_fd(FMT_RESET, STDERR_FILENO);
	ft_putstr_fd(FMT_YELLOW, STDERR_FILENO);
	ft_putstr_fd(msg3, STDERR_FILENO);
	ft_putendl_fd(FMT_RESET, STDERR_FILENO);
}

void	error_fatal(int errcode, char *errmsg, t_cubed *game)
{
	if (errmsg != NULL)
		perror(errmsg);
	free_exit(game, errcode);
}

void	error_exit(int errcode, char *errmsg, t_cubed *game)
{
	if (errmsg != NULL)
	{
		if (errcode == ERR_ARGC)
			error_log("Bad arguments", ": ", errmsg);
		else if (errcode == ERR_MLX)
			error_log (errmsg, ": ", (char *)mlx_strerror(mlx_errno));
		else if (errcode == ERR_MAP)
			error_log(game->map->filename, ": ", errmsg);
		else if (errcode == ERR_ELEM)
			error_log(game->gnl, ": ", errmsg);
		else
			error_log(errmsg, ": ", strerror(errno));
	}
	if (errcode == ERR_MLX)
		free_exit(game, mlx_errno);
	free_exit(game, errcode);
}
