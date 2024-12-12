/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:49:05 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/12 13:46:29 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_Coordinate	**allocatecoordinates(int rows, int cols)
{
	t_Coordinate	**coordinates;
	int				i;
	int				j;

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
		if (coordinates[i] == NULL)
		{
			printf("allocating coordinates failed\n");
			exit(1);
		}
		j = 0;
		while (j < cols)
		{
			coordinates[i][j].z = 2147483648;//obsolete from fdf
			j++;
		}
		i++;
	}
	return (coordinates);
}

void	fd_parse(char *map, t_data *data)
{
	int i;
	char *line;
	int fd;
	i = 0;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	data->fd_parsearray = malloc(sizeof(char *) * 1024);
	while(line)
	{
		data->fd_parsearray[i] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	data->fd_parsearray[i] = NULL;
}


int		find_it(char *ttf,t_data *data)
{
	int i;
	int k;
	i = 0;
	k = 0;
	// printf("line at THE VERY start: %s\n", line);
	while(data->fd_parsearray[i])
	{
		// printf("line at start: %s\n", data->fd_parsearray[i]);
		while(data->fd_parsearray[i][k] == ' ' || data->fd_parsearray[i][k] == 9)
				k++;
		if (ft_strncmp(data->fd_parsearray[i] + k, ttf, 2) == 0)
		{
			
			k = 0;
			// printf("found %s\n", ttf);
			data->flag++;
			// printf("flag is now %d\n", data->flag);
			return(1);
		}
		else
		{
			k = 0;
		}
			i++;
		// printf("line at end %s\n", data->fd_parsearray[i]);
	}
	
	return(0);
}

int		find_colors(char *ttf, t_data *data)
{
	int i;
	int k;
	i = 0;
	k = 0;
	// printf("line at THE VERY start: %s\n", line);
	while(data->fd_parsearray[i])
	{
		// printf("parsing %s\n", data->fd_parsearray[i]);
		// printf("line at start: %s\n", data->fd_parsearray[i]);
		while(data->fd_parsearray[i][k] == ' ' || data->fd_parsearray[i][k] == 9)
				k++;
		if (ft_strncmp(data->fd_parsearray[i] + k, ttf, 1) == 0)
		{
			
			// printf("found %s\n", ttf);
			parse_the_color(data, data->fd_parsearray[i], k);
			data->flag++;
			return(1);
		}
		else
		{
			k = 0;
		}
		i++;
		// printf("line at end %s\n", data->fd_parsearray[i]);
	}
	return(0);
	
}

void	parse_the_color(t_data *data, char *line, int k)
{
	char **temp;
	
	if (line[k] == 'F')
	{
		while (line[k] == 'F' || line[k] == ' ')
			k++;
		temp = ft_split(line + k, ',');
		assign_colors(temp, data);
		data->floorcolor = (data->redc << 16) | (data->greenc << 8) | data->bluec;
	}
	else if (line[k] == 'C')
	{
		while (line[k] == 'C' || line[k] == ' ')
			k++;
		temp = ft_split(line + k, ',');
		assign_colors(temp, data);
		data->ceilingcolor = (data->redc << 16) | (data->greenc << 8) | data->bluec;
	}
	k = 0;
	while (temp[k])
		free(temp[k++]);
	free(temp);
}

void assign_colors(char **temp, t_data *data)
{
	if(ft_isalnumwhole(temp[0]) == 0)
		data->redc = ft_atoi(temp[0]);
	else
	{
		printf("error color assignment\n");
		close_window(data);
	}
	if(ft_isalnumwhole(temp[1]) == 0)
		data->greenc = ft_atoi(temp[1]);
	else
	{
		printf("error color assignment\n");
		close_window(data);
	}
	if(ft_isalnumwhole(temp[2]) == 0)
		data->bluec = ft_atoi(temp[2]);
	else
	{
		printf("error color assignment\n");
		close_window(data);
	}
}


int ft_isalnumwhole(char *line)
{
	int i;
	i = 0;
	while(line[i])
	{
		if ((line[i] >= 48 && line[i] <= 57 && i < 3 )|| line[i] == 10 || line[i] == '\0')
			i++;
		else
			return(1);
	}
	return(0);
}

void	parse_everything_else(char *map, t_data *data)
{
	char *line;
	int fd;
	int i;
	
	data->flag = 0;
	while(data->flag != 6)
	{
		if(data->flag == 0 && (find_it("NO", data) != 1))
			clean_exit(data, "no north found");
		// printf("going southfinding\n");
		if(data->flag == 1 && (find_it("SO", data) != 1))
			clean_exit(data, "no south found");
		if(data->flag == 2 && (find_it("WE", data) != 1))
			clean_exit(data, "no west found");
		if(data->flag == 3 && (find_it("EA", data) != 1))// also dont forget to handle errors
			clean_exit(data, "no east found");
		if(data->flag == 4 && (find_colors("F", data) != 1))
			clean_exit(data, "no floor color found");
		if(data->flag == 5 && (find_colors("C", data) != 1))
			clean_exit(data, "no ceiling color found");
	}
	copy_map_to_buffer(data, 1024);
}

void	copy_map_to_buffer(t_data *data, size_t buffer_size)
{
	size_t	offset = 0;
	int i;
	int k;
	k = 0;
	i = find_the_map(i, data);
	data->rawmaparray = malloc(sizeof(char *) * 1024);
	// printf("copying\n");
	while (data->fd_parsearray[i] && offset < buffer_size)
	{
		size_t len = ft_strlen(data->fd_parsearray[i]);
		if (offset + len >= buffer_size)
		{
			printf("Buffer overflow\n");
			break;
		}
		ft_strlcpy(data->raw_map + offset, data->fd_parsearray[i], len + 1);
		data->rawmaparray[k] = malloc(len + 1);
		ft_strlcpy(data->rawmaparray[k], data->fd_parsearray[i],  len + 1);
		offset += len;
		i++;
		k++;
	}
	data->rawmaparray[k] = NULL;
}

int find_the_map(int i, t_data *data)
{
	while(data->fd_parsearray[i])
	{
		if (ft_strncmp(data->fd_parsearray[i], "111", 3) == 0)
			return(i);
		i++;
	}
	clean_exit(data, "couldn't find a map");
	return(0);
}


char *get_next_line_from_memory(const char *buffer, size_t *offset)
{
    size_t start;
    size_t len;
	char *line;

	len = 0;
	start = *offset;
    if (!buffer[start])
        return NULL;
    while (buffer[start + len] && buffer[start + len] != '\n')
        len++;
   line = malloc(len + 2);
    if (!line)
        return NULL;
    ft_strlcpy(line, buffer + start, len);
    if (buffer[start + len] == '\n')
    {
        line[len] = '\n';
        len++;
    }
    line[len] = '\0';
    *offset = start + len;
	// printf("offset is %zu\n", *offset);
    return line;
}


void parse_map(t_data *data)
{
	size_t offset;
	int fd;
	char *line;
	int i;
	int x;
	int y = 0;
	offset = 0;
	line = get_next_line_from_memory(data->raw_map, &offset);
	// printf("the line is: %s", line);
	while (line != NULL)
	{
		i = 0;
		x = 0;
		while (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == ' ')
		{
			data->coordinates[x/50][y/50].map = line[i];
			render_textures(line[i], data, x, y);
			i++;
			x += 50;
		}
		// x += 50;
		if (line[i] == '\n' || line[i] == '\0')
		{
			data->coordinates[x/50][y/50].map = '1';
			render_textures(line[i], data, x, y);
		}
		if (line[i] != '\0' && line[i] != '\n')
        {
            printf("Found irregularity: %c\n", line[i]);
			freedom(data, line);
        }
		free(line);
		// printf("getting next line\n");
		line = get_next_line_from_memory(data->raw_map, &offset);
		// printf("getting the next line\n");
		// printf("the line is: %s", line);
		y += 50;
	}
	
	// free(line);
	data->colours = 16711680;//deep red (player)
	my_mlx_pixel_put(data, data->posX, data->posY, 5);
	
	printf("finished parsing\n");
	//printing coordinate grid
	// for (int y = 0; y < data->coloumns; y++) 
	// {
    // 	for (int x = 0; x < data->rows; x++)
	// 	{
    //     	printf("Coordinate[%d][%d] = %c\n", x, y, data->coordinates[x][y].map);
    // 	}
	// }
}

void calculatesize(char *map, t_data *data)
{
	char *line;
	int fd;
	int ll;
	size_t offset;
	data->coloumns = 1;
	offset = 0;
	line = get_next_line_from_memory(data->raw_map, &offset);
	ll = 0;
	while(line)
	{
		data->coloumns++;
		ll = ft_strlen(line);
		if (ll > data->rows)
            data->rows = ll;
		free(line);
		line = get_next_line_from_memory(data->raw_map, &offset);
		// printf("data rows: %d, ll: %d\n", data->rows, ll);
	}
	data->rows += 1;
	// free(line);maybe necessary
	printf("rows %d, coloumns %d\n", data->rows, data->coloumns);
}
