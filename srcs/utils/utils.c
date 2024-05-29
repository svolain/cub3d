/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:32:56 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/29 15:33:46 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

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
