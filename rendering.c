/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:48:00 by ckonneck          #+#    #+#             */
/*   Updated: 2024/11/28 15:51:21 by ckonneck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void draw_cube(t_data *data, float x, float y)
{
	float targetx;
	float targety;
	float targetz;
	int i;
	targetx = x + 100;
	while(x <= targetx)//maybe put one more pixel somewhere directly 
	//on the start since 0 is where the detection fails idk
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