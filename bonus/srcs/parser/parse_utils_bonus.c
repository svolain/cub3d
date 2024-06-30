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

char	*ft_skipspaces(char *start, t_cubed *game)
{
	while (*start && *start == ' ')
		start++;
	if (!*start || *start == '\n')
		error_exit(ERR_ELEM, MSG_ELEM, game);
	return (start);
}

static int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	ft_isemptyline(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (!*str)
		return (true);
	return (false);
}
