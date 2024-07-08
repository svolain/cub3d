/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:32:56 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/04 19:06:53 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed_bonus.h>

bool	ft_has_extra_delimiter(char *str, char c)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	if (str[len - 1] == c && c != '\n')
		return (true);
	while (str[i])
	{
		if (i < len && str[i] == c && str[i + 1] == c)
			return (true);
		i++;
	}
	return (false);
}

bool	ft_has_filename(char *file, char *extension)
{
	char	*dot;
	int		len;

	len = ft_strlen(file);
	dot = ft_strrchr(file, '.');
	if (!ft_strncmp(dot - 1, extension, len + 1))
		return (false);
	return (true);
}

bool	ft_has_extension(char *file, char *extension)
{
	char	*dot;
	int		len;

	len = ft_strlen(file);
	dot = ft_strrchr(file, '.');
	if (len < 4 || !dot || ft_strncmp(dot, extension, len + 1))
		return (false);
	return (true);
}

char	*ft_skip_spaces(char *start, t_cubed *game)
{
	while (*start && *start == ' ')
		start++;
	if (!*start || *start == '\n')
		error_exit(ERR_ELEM, MSG_ELEM, game);
	return (start);
}

bool	ft_is_empty_line(char *line)
{
	while (*line && (*line == '\n' || *line == ' '))
		line++;
	if (!*line)
		return (true);
	return (false);
}
