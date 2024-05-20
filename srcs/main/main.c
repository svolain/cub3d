/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:32:06 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/14 09:18:53 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

int	main(int argc, char **argv)
{
	t_cubed	game;

	argc = 0;
	// if (argc != 2)
	// 	error_exit(ERR_ARGC, MSG_ARGC, NULL);
	init_game(&game, argv[1]);
	mlx_loop(game.mlx);
	free_exit(&game, NOERROR);
	/* return (NOERROR); */
}
