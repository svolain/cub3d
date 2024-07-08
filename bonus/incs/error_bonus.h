/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:28:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 09:25:09 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_BONUS_H
# define ERROR_BONUS_H

# define MSG_ARGC	"./cub3d maps/<filename>.cub"
# define MSG_EXTN	"Invalid file extension"
# define MSG_NAME	"File has no name"
# define MSG_FLDR	"Is a directory"
# define MSG_EMPTY	"Is an empty file"
# define MSG_ELEM	"Invalid element"
# define MSG_ASSET	"Missing an element"
# define MSG_NOMAP	"Map was not found"
# define MSG_SMALL	"Map dimension(s) is too small"
# define MSG_LARGE	"Map dimension(s) is too large <100>"
# define MSG_WALL	"Map has no properly closed walls"
# define MSG_PLAY	"Map has no or more than one player(s)"
# define MSG_CHAR	"Map has invalid character(s)"
# define MSG_BLANK	"Map has empty line(s)"

# define MSG_MEM	"Could not malloc"
# define MSG_MLX	"MLX42 error"
# define MSG_SYSC	"System call error in "

# define FMT_BOLD_RED	"\033[1;31m"
# define FMT_YELLOW		"\033[0;33m"
# define FMT_RESET		"\033[0m"

enum e_errcodes
{
	NOERROR,
	ERR_ARGC,
	ERR_MAP,
	ERR_ELEM,
	ERR_MLX
};

#endif
