/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:26:10 by dyao              #+#    #+#             */
/*   Updated: 2024/12/30 15:26:14 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	checkforduplicates(t_data *data)
{
	int	i;
	int	k;

	i = 0;
	while (data->squaremap[i])
	{
		k = 0;
		while (data->squaremap[i][k])
		{
			if (data->squaremap[i][k] == 'N' || data->squaremap[i][k] == 'E'
				|| data->squaremap[i][k] == 'W' || data->squaremap[i][k] == 'S')
				data->playerflag++;
			k++;
		}
		i++;
	}
	if (data->playerflag > 1)
		seperate_clean_exit(data, "duplicates hakken\n");
}

void	checkiftheresanother(t_data *data, int i, char *ttf)
{
	int	k;

	k = 0;
	i += 1;
	while (data->fd_parsearray[i])
	{
		while (data->fd_parsearray[i][k] == ' '
			|| data->fd_parsearray[i][k] == 9)
			k++;
		if (ft_strncmp(data->fd_parsearray[i] + k, ttf, 2) == 0)
		{
			tex_clean_exit(data, "found duplicate texturepath");
		}
		else
			k = 0;
		i++;
	}
}
