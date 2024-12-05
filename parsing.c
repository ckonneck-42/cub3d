/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:49:05 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/05 15:39:31 by ckonneck         ###   ########.fr       */
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

int		find_it(char *line, int fd, char *ttf)
{
	int i;
	i = 0;
	line = get_next_line(fd);
	while(line)
	{
		while(line[i] == ' ')
				i++;
		if (ft_strncmp(line+i, ttf, 2) == 0)
		{
			i = 0;
			free(line);
			line = get_next_line(fd);
			printf("found %s\n", ttf);
			return(1);
		}
		else
		{
			i = 0;
			free(line);
			line = get_next_line(fd);
		}
		printf("%s", line);
	}
	return(0);
	
}


void	parse_everything_else(char *map, t_data *data)
{
	char *line;
	int fd;
	int i;
	fd = open(map, O_RDONLY);

		if(find_it(line, fd, "NO") != 1)
			printf("no north found\n");
		printf("going into southfinding\n");
		if(find_it(line, fd, "SO") != 1)
			printf("no south found\n");
		printf("going into westfinding\n");
		if(find_it(line, fd, "WE") != 1)
			printf("no west found\n");
		if(find_it(line, fd, "EA") != 1)
			printf("no east found\n");
		// else
		// {
		// 	free(line);
		// 	get_next_line(fd);
		// }
	close (fd);
	exit(0);
}

void parse_map(char *map, t_data *data)
{
	int fd;
	char *line;
	int i;
	int x;
	// parse_everything_else(map, data);
	int y = 0;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
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
		line = get_next_line(fd);
		y += 50;
	}
	close(fd);
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
