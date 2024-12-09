/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:49:05 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/09 16:15:43 by ckonneck         ###   ########.fr       */
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
		printf("line at start: %s\n", data->fd_parsearray[i]);
		while(data->fd_parsearray[i][k] == ' ' || data->fd_parsearray[i][k] == 9)
				k++;
		if (ft_strncmp(data->fd_parsearray[i] + k, ttf, 2) == 0)
		{
			
			k = 0;
			printf("found %s\n", ttf);
			data->flag++;
			printf("flag is now %d\n", data->flag);
			return(1);
		}
		else
		{
			k = 0;
		}
			i++;
		printf("line at end %s\n", data->fd_parsearray[i]);
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
		printf("line at start: %s\n", data->fd_parsearray[i]);
		while(data->fd_parsearray[i][k] == ' ' || data->fd_parsearray[i][k] == 9)
				k++;
		if (ft_strncmp(data->fd_parsearray[i] + k, ttf, 1) == 0)
		{
			
			k = 0;
			printf("found %s\n", ttf);
			data->flag++;
			printf("flag is now %d\n", data->flag);
			return(1);
		}
		else
		{
			k = 0;
		}
			i++;
		printf("line at end %s\n", data->fd_parsearray[i]);
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
		{
			perror("no north found");
			exit(1);
		}
		printf("going southfinding\n");
		if(data->flag == 1 && (find_it("SO", data) != 1))
		{
			perror("no south found");
			exit(1);
		}
		if(data->flag == 2 && (find_it("WE", data) != 1))
		{
			perror("no west found");
			exit(1);
		}
		if(data->flag == 3 && (find_it("EA", data) != 1))// also dont forget to handle errors
		{
			perror("no east found");
			exit(1);
		}
		if(data->flag == 4 && (find_colors("F", data) != 1))
			perror("no floor color found");
		if(data->flag == 5 && (find_colors("C", data) != 1))
			perror("no ceiling color found");
	}
		copy_map_to_buffer(data, 1024);//need to change this because i stopped passing fd.
		close (fd);
}

void	copy_map_to_buffer(t_data *data, size_t buffer_size)
{
	size_t	offset = 0;
	int i;
	i = find_the_map(i, data);
	
	while (data->fd_parsearray[i] && offset < buffer_size)
	{
		size_t len = ft_strlen(data->fd_parsearray[i]);
		if (offset + len >= buffer_size)
		{
			fprintf(stderr, "Buffer overflow\n");
			break;
		}
		ft_strlcpy(data->raw_map + offset, data->fd_parsearray[i], len + 1);
		offset += len;
		i++;
	}
}

int find_the_map(int i, t_data *data)
{
	while(data->fd_parsearray[i])
	{
		if (ft_strncmp(data->fd_parsearray[i], "111", 3) == 0)
			return(i);
		i++;
	}
	perror("couldn't find a map");
	exit(1);
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
	while (line != NULL)
	{
		i = 0;
		x = 0;
		while (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == ' ')
		{
			if (line[i] == '1')
				data->coordinates[x/50][y/50].map = line[i];
			else
				data->coordinates[x/50][y/50].map = line[i];
			render_textures(line[i], data, x, y);
			i++;
			x += 50;
		}
		if (line[i] == '\n' || line[i] == '\0')
			data->coordinates[x/50][y/50].map = '1';
		if (line[i] != '\0' && line[i] != '\n')
        {
            printf("Found irregularity: %c\n", line[i]);
			freedom(data, line);
        }
		free(line);
		// printf("getting next line\n");
		line = get_next_line_from_memory(data->raw_map, &offset);
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
	data->coloumns = 0;
	fd = open(map, O_RDONLY);
	ll = 0;
	line = get_next_line(fd);
	while(line)
	{
		data->coloumns++;
		ll = ft_strlen(line);
		if (ll > data->rows)
            data->rows = ll;
		free(line);
		line = get_next_line(fd);
	}
	// free(line);maybe necessary
	close(fd);
	printf("rows %d, coloumns %d\n", data->rows, data->coloumns);
	// printf("coloumsize = %d", data->coloumn);
}
