/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:37 by ckonneck          #+#    #+#             */
/*   Updated: 2024/11/26 13:28:38 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	render_textures(char target, t_data *data, int x, int y)
{
	int img_width, img_height;
	t_Cube cube;
	t_RaycastVars ray;
	cube.height = 256;

	if (!data->img[1])
		data->img[1] = mlx_xpm_file_to_image(data->mlx, TEXTURE_METAL, &cube.height, &cube.height);
	if (!data->img[2])
		data->img[2] = mlx_xpm_file_to_image(data->mlx, TEXTURE_SNOW, &cube.height, &cube.height);
	// 	data->img[3] = mlx_xpm_file_to_image(data->mlx, TEXTURE_METAL, &img_width, &img_height);
	if (target == '1')
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img[1],
			x, y);
		printf("put 1\n");
	}
	else if (target == '0')
		mlx_put_image_to_window(data->mlx, data->win, data->img[2],
			x, y);
	else if (target == 'N')
	{
		my_mlx_pixel_put(data, data->posX, data->posY, 20);
		// mlx_put_image_to_window(data->mlx, data->win, data->img[0],  if i dont update the screen it doesnt show
		// 	x, y);
	}
		 // Draw a white dot for the player
		//putplayer/camera here facing the right way ofc
	//also give 4 sets based on the NO SO WE shit orientation so that i load images based off of that.
	
	// else if (target == 'N')
	// 	render_player(data, x, y);
	// else if (target == 'Z')
	// 	render_enemy(game, x, y);
	// else if (target == 'C')
	// 	render_collectible(game, x, y);
	// else if (target == 'E')
	// 	render_exit(game, x, y);
}



void	my_mlx_pixel_put(t_data *data, float x, float y, int size)
{
	char	*dst;
	int		i;
	int		j;
	data->colours = 20000;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + i >= 0 && x + i < 1920 && y + j >= 0 && y + j < 1080)
			{
				dst = data->addr + ((int)(y + j) *data->line_length + (int)(x
							+ i) *(data->bits_per_pixel / 8));
				*(unsigned int *)dst = data->colours;
			}
			j++;
		}
		i++;
	}
}



void parse_map(char **argv, t_data *data)
{
	int fd;
	fd = open(argv[1], O_RDONLY);
	char *line;
	int i;
	line = get_next_line(fd);
	int x;
	int y = 0;
	while (line != NULL)
	{
		x = 0;
		while (line[i] == '1' || line[i] == '0' || line[i] == 'N' || line[i] == ' ')
		{
			render_textures(line[i], data, x, y);
			i++;
			x += 50;
		}
		if(line[i+1] == '\0')
		{
			printf("reached end of line\n");
		}
		else
		{
			printf("found irregularity: %c\n", line[i]);
			exit(1);
		}
		i = 0;
		free(line);
		printf("getting next line\n");
		line = get_next_line(fd);
		y += 50;
	}
	printf("finished parsing\n");
}


int main(int argc, char **argv)
{
	t_data *data;
	data = base_init(data);
	if (argc != 2)
	{
		printf("give map plx\n");
		exit(1);
	}
	else
		parse_map(argv, data);
		
	// raycasting(&data);
	
	// mlx_put_image_to_window(data->mlx, data->win, data->img[0], 0, 0);

	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L << 0, ft_close, data);
	mlx_key_hook(data->win, keypress, data);
	mlx_loop(data->mlx);

}


t_data	*base_init(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1920, 1080, "cub3d");
	data->img[0] = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img[0], &data->bits_per_pixel,
			&data->line_length, &data->endian);
	data->posX = 960;
	data->posY = 540;  //x and y start position
  	data->dirX = 1;
	data->dirY = 0; //initial direction vector
  	data->planeX = 0;
	data->planeY = 0.66; //the 2d raycaster version of camera plane
	data->movespeed = 0.05;
	return(data);
};

