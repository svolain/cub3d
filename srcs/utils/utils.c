/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:32:56 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/27 17:01:58 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>

void	ft_rotate(float *target, float angle, t_action action)
{
	if (action == ROTATE_LEFT)
	{
		*target -= angle;
		if (*target < 0)
			*target += 2 * PI;
	}
	else if (action == ROTATE_RIGHT)
	{
		*target += angle;
		if (*target > 2 * PI)
			*target -= 2 * PI;
	}
}

float	ft_degtorad(float degree)
{
	return (degree * PI / 180);
}

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

	temp = malloc(sizeof(char *) * (height + 1));
	if (!temp)
		error_fatal(ENOMEM, MSG_MEM, game);
	i = 0;
	while(i < height)
	{
		temp[i] = ft_strdup(arr[i]);
		if (temp[i] == NULL)
			error_fatal(ENOMEM, MSG_MEM, game);
		i++;
	}
	temp[i] = 0;
	return (temp);
}
