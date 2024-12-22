/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:41:30 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/22 15:37:21 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fd_parse(char *map, t_data *data)
{
	int		i;
	char	*line;
	int		fd;

	i = 0;
	checkfilename(data, map);
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	data->fd_parsearray = malloc(sizeof(char *) * 1024);
	while (line)
	{
		data->fd_parsearray[i] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	data->fd_parsearray[i] = NULL;
}

int	find_it(char *ttf, t_data *data)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (data->fd_parsearray[i])
	{
		while (data->fd_parsearray[i][k] == ' '
			|| data->fd_parsearray[i][k] == 9)
			k++;
		if (ft_strncmp(data->fd_parsearray[i] + k, ttf, 2) == 0)
		{
			parse_the_texturepath(data, data->fd_parsearray[i], k, ttf);
			k = 0;
			data->flag++;
			return (1);
		}
		else
			k = 0;
		i++;
	}
	return (0);
}

void	parse_everything_else(char *map, t_data *data)
{
	char	*line;
	int		fd;
	int		i;

	data->flag = 0;
	while (data->flag != 6)
	{
		if (data->flag == 0 && (find_it("NO", data) != 1))
			tex_clean_exit(data, "no north found");
		if (data->flag == 1 && (find_it("SO", data) != 1))
			tex_clean_exit(data, "no south found");
		if (data->flag == 2 && (find_it("WE", data) != 1))
			tex_clean_exit(data, "no west found");
		if (data->flag == 3 && (find_it("EA", data) != 1))
			tex_clean_exit(data, "no east found");
		if (data->flag == 4 && (find_colors("F", data) != 1))
			tex_clean_exit(data, "no floor color found");
		if (data->flag == 5 && (find_colors("C", data) != 1))
			tex_clean_exit(data, "no ceiling color found");
	}
	ft_wall_texture(data);
	copy_map_to_buffer(data, 21000000);
}

void	copy_map_to_buffer(t_data *data, size_t buffer_size)
{
	size_t	offset;
	int		i;
	int		k;
	size_t	len;

	offset = 0;
	k = 0;
	i = find_the_map(i, data);
	while (data->fd_parsearray[i] && offset < buffer_size)
	{
		len = ft_strlen(data->fd_parsearray[i]);
		if (offset + len >= buffer_size)
		{
			data->rawmaparray[k] = NULL;
			seperate_clean_exit(data, "map too large");
		}
		ft_strlcpy(data->raw_map + offset, data->fd_parsearray[i], len + 1);
		data->rawmaparray[k] = malloc(len + 1);
		ft_strlcpy(data->rawmaparray[k], data->fd_parsearray[i], len + 1);
		offset += len;
		i++;
		k++;
	}
	data->rawmaparray[k] = NULL;
}

int	find_the_map(int i, t_data *data)
{
	int	k;

	while (data->fd_parsearray[i])
	{
		k = 0;
		while (data->fd_parsearray[i][k] == ' '
			|| data->fd_parsearray[i][k] == '\t')
			k++;
		if (ft_strncmp(&data->fd_parsearray[i][k], "1", 1) == 0)
			return (i);
		i++;
	}
	seperate_clean_exit(data, "couldn't find a map");
	return (0);
}
