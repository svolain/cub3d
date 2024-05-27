/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:19:07 by vsavolai          #+#    #+#             */
/*   Updated: 2024/05/27 19:15:32 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

char	*safe_strjoin(char *s1, char *s2, t_cubed *game)
{
	char	*s;

	s = ft_strjoin(s1, s2);
	if (!s)
		error_fatal(ENOMEM, MSG_MEM, game);
	return (s);
}
