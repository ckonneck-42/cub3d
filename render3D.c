/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyao <dyao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 19:28:24 by dyao              #+#    #+#             */
/*   Updated: 2024/12/21 19:47:23 by dyao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_all(t_data *data, int screenColumn, double distance)
{
	if ((int)data->final_point[screenColumn].x % GRID_SIZE == 0
		&& (int)data->final_point[screenColumn].y % GRID_SIZE == 0)
		draw_middle(data, screenColumn);
	else if (((int)data->final_point[screenColumn].x % GRID_SIZE == 0)
		&& data->final_point[screenColumn].x > data->posX)
		ft_draw_wall(data, screenColumn, distance, 0);
	else if (((int)data->final_point[screenColumn].x % GRID_SIZE == 0)
		&& data->final_point[screenColumn].x < data->posX)
		ft_draw_wall(data, screenColumn, distance, 1);
	else if (((int)data->final_point[screenColumn].y % GRID_SIZE == 0)
		&& data->final_point[screenColumn].y > data->posY)
		ft_draw_wall_2(data, screenColumn, distance, 2);
	else if (((int)data->final_point[screenColumn].y % GRID_SIZE == 0)
		&& data->final_point[screenColumn].y < data->posY)
		ft_draw_wall_2(data, screenColumn, distance, 3);
}

void	render3d(t_data *data, double distance,
		double cubeHeight, int screenColumn)
{
	if (screenColumn < 0 || screenColumn > data->screenWidth)
		printf("Error: screenColumn (%d) out of bounds!\n", screenColumn);
	data->wallstarty = (data->screenHeight / 2) - ((cubeHeight
				* (data->screenWidth / 2) / tan(data->FOV / 2)) / distance / 2);
	data->wallendy = (data->screenHeight / 2) + ((cubeHeight
				* (data->screenWidth / 2) / tan(data->FOV / 2)) / distance / 2);
	data->walltotal = data->wallendy - data->wallstarty;
	data->wall_true_start_y = data->wallstarty;
	if (screenColumn < 500)
		if (data->wallstarty < 300)
			data->wallstarty = 300;
	if (data->wallstarty < 0)
		data->wallstarty = 0;
	if (data->wallendy > data->screenHeight)
		data->wallendy = data->screenHeight - 1;
	draw_all(data, screenColumn, distance);
}

int	ft_detectgrid(t_data *data, double x, double y)
{
	int	gridx;
	int	gridy;

	gridx = (int)((x) / GRID_SIZE);
	gridy = (int)((y) / GRID_SIZE);
	if (data->check_x && data->check_y && (int)x == data->check_x
		&& (int)y == data->check_y)
		return (0);
	if (gridx < 0 || gridy < 0)
		return (0);
	if (gridx >= data->rows || gridy >= data->coloumns
		|| !data->coordinates[gridx])
		return (1);
	if (data->coordinates[gridx][gridy].map == '1')
		return (1);
	if (ft_detectgrid_2(data, x, y))
		return (1);
	data->check_x = (int)x;
	data->check_y = (int)y;
	return (0);
}

void	smallmap(t_data *data)
{
	double	x;
	double	a;
	double	y;
	double	b;

	a = 0;
	x = data->posX - 250;
	data->colours = 6666666;
	while (x <= (data->posX + 250))
	{
		y = data->posY - 150;
		b = 0;
		while (y <= data->posY + 150)
		{
			if (ft_detectgrid(data, x, y))
				my_mlx_pixel_put(data, a, b, 1);
			y += 1;
			b += 1;
		}
		x += 1;
		a += 1;
	}
	data->colours = 9999999;
	my_mlx_pixel_put(data, 250, 150, 10);
}

void	renderscene(t_data *data)
{
	int	screencolumn;

	screencolumn = 0;
	while (screencolumn < data->screenWidth)
	{
		render3d(data, data->distanceahead[screencolumn],
			GRID_SIZE * 4 / 5, screencolumn);
		screencolumn++;
	}
	smallmap(data);
}
