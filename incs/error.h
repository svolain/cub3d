/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:28:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/25 19:48:01 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MSG_ARGC		"./cub3d maps/<filename>.cub"
# define MSG_EXTN		"Invalid file extension <cub>"
# define MSG_NAME		"Invalid filename"
# define MSG_FLDR		"Is a directory"
# define MSG_ELEM		"Invalid map element"
# define MSG_VOID		"Map is an empty file"
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
	ERR_ELEM,
	ERR_MLX
};

#endif
