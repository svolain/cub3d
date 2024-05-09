/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:28:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/08 21:25:42 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MSG_ARGC		"./cub3d maps/<filename>.cub"
# define MSG_EXTN		"Incorrect file extension <cub>"
# define MSG_FILE		"No such file or directory"
# define MSG_FLDR		"Is a directory"
# define MSG_PERM		"Permission denied"
# define MSG_EMPTY		"Map is empty"
# define MSG_LINE		"Map has empty line(s)"
# define MSG_RECT		"Map is not rectangular"
# define MSG_PLAYER		"Map has no or more than one player(s)"
# define MSG_EXIT		"Map has no or more than one exit(s)"
# define MSG_PICKUP		"Map has no pickup(s)"
# define MSG_CHAR		"Map has invalid character(s)"
# define MSG_WALL		"Map has no properly closed walls"
# define MSG_PATH		"Map has no valid path to exit"
# define MSG_PICK		"Map has no valid path to pickup(s)"
# define MSG_MEM		"Could not malloc"
# define MSG_MLX		"MLX42 error"

enum e_errcodes
{
	NOERROR,
	ERR_ARGC,
	ERR_MAP,
	ERR_MLX
};

#endif
