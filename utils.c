/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:59:14 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/22 15:53:13 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_char_at(t_data *data, int x, int y)
{
	return (data->squaremap[y][x]);
}

void	set_char_at(t_data *data, int x, int y, char new)
{
	data->squaremap[y][x] = new;
}
// if we have parsing errors, might be data->coloumns +1 or + 2

int	get_nr_of_lines(t_data *data)
{
	int	i;

	i = 0;
	while (data->squaremap[i] && i < data->coloumns + 1)
	{
		i++;
	}
	return (i - 1);
}

void	complete_flood(t_data *data, int x, int y)
{
	checktheplayer(data);
	flood_fill(data, x, y);
	fill_from_zero(data);
}

int	ft_isalnumwhole(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
		return (1);
	while (line[i])
	{
		if ((line[i] >= 48 && line[i] <= 57 && i < 3) || line[i] == 10
			|| line[i] == '\0')
			i++;
		else
			return (1);
	}
	return (0);
}
