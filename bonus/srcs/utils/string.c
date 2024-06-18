/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:51:45 by jmertane          #+#    #+#             */
/*   Updated: 2024/06/11 06:13:54 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	free_single(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

void	free_double(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free_single(&(*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

char	*safe_strjoin(char *s1, char *s2, t_cubed *game)
{
	char	*s;

	s = ft_strjoin(s1, s2);
	if (!s)
	{
		free_single(&s1);
		free_single(&s2);
		error_fatal(ENOMEM, MSG_MEM, game);
	}
	return (s);
}

char	*safe_substr(char *stt, char *end, t_cubed *game)
{
	char	*s;

	s = ft_substr(stt, 0, end - stt);
	if (!s)
		error_fatal(ENOMEM, MSG_MEM, game);
	return (s);
}

char	**safe_split(char *str, char c, t_cubed *game)
{
	char	**s;

	s = ft_split(str, c);
	if (!s)
	{
		free_single(&str);
		error_fatal(ENOMEM, MSG_MEM, game);
	}
	return (s);
}
