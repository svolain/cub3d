/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:32:56 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/28 12:37:42 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

char	*ft_skip_whitespace(char *str)
{
	while (*str != 0 && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	return (str);
}

int	ft_arrlen(char **arr)
{
	int i = 0;

	while(arr[i] != 0)
		i++;
	return (i);
}

char	**dup_arr(char **arr, int height, t_cubed *game)
{
	char	**temp;
	int		i;
	int		len;
	int		map_width;

	len = 0;
	map_width = 0;
	temp = malloc(sizeof(char *) * (height + 1));
	if (!temp)
		error_fatal(ENOMEM, MSG_MEM, game);
	i = 0;
	while(i < height)
	{
		if (len >= map_width)
			map_width = len;
		temp[i] = ft_strdup(arr[i]);
		if (temp[i] == NULL)
			error_fatal(ENOMEM, MSG_MEM, game);
		len = ft_strlen(arr[i]);
		i++;
	}
	game->map->width = map_width;
	temp[i] = 0;
	return (temp);
}
