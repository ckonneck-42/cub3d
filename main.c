/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:37 by ckonneck          #+#    #+#             */
/*   Updated: 2024/11/27 16:54:40 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void draw_cube(t_data *data, float x, float y)
{
	float targetx;
	float targety;
	float targetz;
	int i;
	targetx = x + 100;
	while(x <= targetx)
	{
		// if(get_pixel_color(x+10, y, data) == 45000)
		// 	break;
		my_mlx_pixel_put(data, x, y, 1);
		x++;
	}
	targety = y + 100;
	while(y <= targety)
	{	
		// if(get_pixel_color(x, y+10, data) == 45000)
		// 	break;
		my_mlx_pixel_put(data, x, y, 1);
		y++;
	}
	targetx = x - 100;
	while(x >= targetx)
	{
		// if(get_pixel_color(targetx-10, y, data) == 45000)
		// 	break;
		my_mlx_pixel_put(data, x, y, 1);
		x--;
	}
	targety = y - 100;
	while(y >= targety)
	{
		// if(get_pixel_color(x, targety-10, data) == 45000)
		// 	break;
		my_mlx_pixel_put(data, x, y, 1);
		y--;
	}
}

void	render_textures(char target, t_data *data, int x, int y)
{
	t_Cube cube;
	t_RaycastVars ray;
	cube.height = 256;
	int nr;
	nr = 0;
	// if (!data->img[1])
	// 	data->img[1] = mlx_xpm_file_to_image(data->mlx, TEXTURE_METAL, &cube.height, &cube.height);
	// if (!data->img[2])
	// 	data->img[2] = mlx_xpm_file_to_image(data->mlx, TEXTURE_SNOW, &cube.height, &cube.height);
	// 	data->img[3] = mlx_xpm_file_to_image(data->mlx, TEXTURE_METAL, &img_width, &img_height);
	if (target == '1')
	{
		draw_cube(data, x, y);
		// savecoords(x, y, nr++);
	}
	// else if (target == '0')
	// 	my_mlx_pixel_put(data, x, y, 10);
	// 	// mlx_put_image_to_window(data->mlx, data->win, data->img[2],
	// 	// 	x, y);
	else if (target == 'N' && data->flag == 0)
	{
		// printf("saving player coords");
		data->posX = x;
		data->posY = y;
		data->flag = 1;
		// mlx_put_image_to_window(data->mlx, data->win, data->img[0],  if i dont update the screen it doesnt show
		// 	x, y);
	}
	//instead of doing prev_x, we just go square, we go up down left right, whatever, set amount of pixels
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

void	savecoords(int x, int y, int nr)
{
	
}


void	my_mlx_pixel_put(t_data *data, float x, float y, int size)
{
	char	*dst;
	int		i;
	int		j;
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
			x += 100;
		}
		if(line[i+1] == '\0')
		{
			// printf("reached end of line\n");
		}
		else
		{
			printf("found irregularity: %c\n", line[i]);
			exit(1);
		}
		i = 0;
		free(line);
		// printf("getting next line\n");
		line = get_next_line(fd);
		y += 100;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img[0], 0, 0);
	printf("finished parsing\n");
}


int main(int argc, char **argv)
{
	t_data *data;
	data = base_init(data);
	data->map = argv;
	if (argc != 2)
	{
		printf("give map plx\n");
		exit(1);
	}
	else
		parse_map(argv, data);
		
	// raycasting(&data);
	
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
	// data->img[1] = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img[0], &data->bits_per_pixel,
			&data->line_length, &data->endian);
	// data->addr1 = mlx_get_data_addr(data->img[1], &data->bits_per_pixel,
    //                             &data->line_length, &data->endian);
	data->colours = 45000;
	data->posX = 960;
	data->posY = 540;  //x and y start position
  	data->dirX = 1;
	data->dirY = 0; //initial direction vector
  	data->planeX = 0;
	data->planeY = 1.0; //the 2d raycaster version of camera plane
	data->movespeed = 7.0;
	data->a = 0;
	data->flag = 0;
	return(data);
};

