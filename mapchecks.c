/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapchecks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:04:48 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/21 17:20:51 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_a_square(t_data *data)
{
	int	i;

	i = 0;
	data->squaremap = malloc((data->coloumns + 2) * sizeof(char *));
	while (i < data->coloumns + 2)
		data->squaremap[i++] = NULL;
	i = 0;
	while (i < data->coloumns + 1)
	{
		data->squaremap[i] = malloc((data->rows + 3) * sizeof(char));
		ft_memset(data->squaremap[i], '2', data->rows + 2);
		data->squaremap[i][data->rows + 2] = '\0';
		i++;
	}
	make_btwo(data);
}

void	make_btwo(t_data *data)
{
	int	i;
	int	k;
	int	len;
	int	x;

	len = 0;
	i = 1;
	k = 0;
	x = 0;
	while (i < data->coloumns)
	{
		len = ft_strlen(data->rawmaparray[k]);
		if (i == data->coloumns - 1)
			ft_memcpy(data->squaremap[i] + 1, data->rawmaparray[k], len);
		else
			ft_memcpy(data->squaremap[i] + 1, data->rawmaparray[k], len - 1);
		data->squaremap[i][data->rows + 2] = '\0';
		i++;
		k++;
	}
}

void	restore_map(t_data *data)
{
	int	i;
	int	k;
	int	x;

	i = 0;
	k = 0;
	while (data->squaremap[i])
	{
		k = 0;
		while (data->squaremap[i][k])
		{
			if (data->squaremap[i][k] == 'F')
				data->squaremap[i][k] = '0';
			k++;
		}
		i++;
	}
	x = 0;
}

void	calculatesize(char *map, t_data *data)
{
	char	*line;
	int		fd;
	int		ll;
	size_t	offset;

	data->coloumns = 1;
	offset = 0;
	line = get_next_line_from_memory(data->raw_map, &offset);
	ll = 0;
	while (line)
	{
		data->coloumns++;
		ll = ft_strlen(line);
		if (ll > data->rows)
			data->rows = ll;
		free(line);
		line = get_next_line_from_memory(data->raw_map, &offset);
	}
	data->rows += 1;
}

void	checkfilename(t_data *data, char *map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	i = i - 4;
	if (map[i] == '.' && map[i + 1] == 'c' && map[i + 2] == 'u' && map[i
			+ 3] == 'b')
		return ;
	else
		clean_exit(data, "invalid mapname");
}
