/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:28:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/22 14:41:00 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MSG_ARGC		"./cub3d maps/<filename>.cub"
# define MSG_EXTN		"Incorrect file extension <cub>"
# define MSG_FNM		"Invalid filename"
# define MSG_FILE		"No such file or directory"
# define MSG_FLDR		"Is a directory"
# define MSG_PERM		"Permission denied"
# define MSG_MPEL		"Incorrect map element"
# define MSG_VOID		"Map provided is empty file"
# define MSG_PLAY		"Map has no or more than one player(s)"
# define MSG_CHAR		"Map has invalid character(s)"
# define MSG_WALL		"Map has no properly closed walls"
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
