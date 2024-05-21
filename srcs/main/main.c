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


	// if (argc != 2)
	// 	error_exit(ERR_ARGC, MSG_ARGC, NULL);
	init_game(&game, argv[1]);
	mlx_close_hook(game.mlx, &hook_close, &game);
	/* mlx_loop_hook(game.mlx, &hook_keys, game.mlx); */
	mlx_key_hook(game.mlx, &hook_keys, &game);
	mlx_loop(game.mlx);
	free_exit(&game, NOERROR);
	/* return (NOERROR); */
}
