/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:14:37 by ckonneck          #+#    #+#             */
/*   Updated: 2024/12/19 17:25:16 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
	t_data *data;
	data = base_init(data, argv);
	if (argc != 2)
	{
		printf("give map plx\n");
		exit(1);
	}
	else
	{
		fd_parse(data->map, data);
		parse_everything_else(data->map, data);
		calculatesize(data->map, data);
		make_a_square(data);
		data->coordinates = allocatecoordinates(data->rows + 3, data->coloumns + 1);
		parse_map(data);
		if(is_surrounded(data) == 1)
			clean_exit(data, "invalid map");
		restore_map(data);
		castbeams(data);
		renderScene(data);
	}
	
	data->colours = 45000;
	// mlx_put_image_to_window(data->mlx, data->win, data->img[0], 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->img[0], 0, 0);

	
	// 	int img_width;
	// int img_height;
	// void *img;
	// img = mlx_xpm_file_to_image(data->mlx, "./pic/NO.xpm", &img_width, &img_height);
	// mlx_put_image_to_window(data->mlx, data->win, img, 960, 540);
	// raycasting(&data);
	
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L << 0, ft_close, data);
	mlx_key_hook(data->win, keypress, data);
	mlx_loop(data->mlx);

}



t_data	*base_init(t_data *data, char **argv)
{
	data = malloc(sizeof(t_data));
	data->map = argv[1];
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
	data->movespeed = 10.0;
	data->playerflag = 0;
	data->a = 0;
	data->playerAngle = 0;
	data->flag = 0;
	data->coloumns = 0;
	data->rows = 0;
	data->FOV = 60 * PI / 180;
	data->screenHeight = 1080;
	data->screenWidth = 1920;
	return(data);
};

