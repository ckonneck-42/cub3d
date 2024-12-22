/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:49:05 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/22 14:37:36 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_next_line_from_memory(const char *buffer, size_t *offset)
{
	size_t	start;
	size_t	len;
	char	*line;

	len = 0;
	start = *offset;
	if (!buffer[start])
		return (NULL);
	while (buffer[start + len] && buffer[start + len] != '\n')
		len++;
	line = malloc(len + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer + start, len);
	if (buffer[start + len] == '\n')
	{
		line[len] = '\n';
		len++;
	}
	line[len] = '\0';
	*offset = start + len;
	return (line);
}

void	parse_map(t_data *data)
{
	char	*line;
	int		i;
	int		x;
	int		y;
	int		k;

	i = 0;
	y = 0;
	k = 0;
	while (data->squaremap[k] != NULL)
	{
		line = data->squaremap[k];
		x = 0;
		i = parse_map2(data, line, x, y);
		parse_map3(data, i, line);
		y += GRID_SIZE;
		k++;
	}
	if (data->playerflag == 0)
		clean_exit(data, "no player found");
	data->colours = 16711680;
}

int	parse_map2(t_data *data, char *line, int x, int y)
{
	int	i;

	i = 0;
	while (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == ' '
		|| line[i] == '2' || line[i] == 'E' || line[i] == 'W' || line[i] == 'S'
		|| line[i] == '\t')
	{
		if (line[i] == '1' || line[i] == '2')
			data->coordinates[x / GRID_SIZE][y / GRID_SIZE].map = '1';
		else
			data->coordinates[x / GRID_SIZE][y / GRID_SIZE].map = line[i];
		render_textures(line[i], data, x, y);
		i++;
		x += GRID_SIZE;
	}
	return (i);
}

void	parse_map3(t_data *data, int i, char *line)
{
	if (line[i] != '\0' && line[i] != '\n' && line[i] != '2' && line[i] != '\t'
		&& line[i] != 'F')
	{
		printf("Found irregularity: %c\n", line[i]);
		freedom(data, line);
	}
}

t_Coordinate	**alloco(int rows, int cols)
{
	t_Coordinate	**coordinates;
	int				i;
	int				k;

	i = 0;
	coordinates = (t_Coordinate **)malloc(rows * sizeof(t_Coordinate *));
	if (coordinates == NULL)
	{
		ft_printf("Memory allocation failed for rows\n");
		exit(1);
	}
	while (i < rows)
	{
		coordinates[i] = (t_Coordinate *)malloc(cols * sizeof(t_Coordinate));
		k = 0;
		while (k < cols)
		{
			coordinates[i][k].x = 0;
			coordinates[i][k].y = 0;
			coordinates[i][k].map = '1';
			k++;
		}
		i++;
	}
	return (coordinates);
}
