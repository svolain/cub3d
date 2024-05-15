/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:48:30 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/15 07:43:56 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

char	*safe_strjoin(char *s1, char *s2, char **buf, t_cubed *game)
{
	char	*s;

	if (!s1 || !s2)
		return ;
	s = ft_strjoin(s1, s2);
	if (!s)
	{
		free(*buf);
		error_fatal(ENOMEM, MSG_MEM, ms);
	}
	return (s);
}

void	*safe_calloc(size_t n, t_cubed *game)
{
	void	*p;

	p = ft_calloc(1, n);
	if (!p)
		error_fatal(ENOMEM, MSG_MEM, game);
	return (p);
}